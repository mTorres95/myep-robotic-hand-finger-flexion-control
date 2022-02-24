/*
 * i2c.c
 *
 *  Author: miact
 */ 

#include "main.h"

/*	
	Baudrate configuration for I2C interface
	This is done when the device is master
	The master sets the SCL speed
	Considers prescaler = 1
*/
void I2C_init_master(uint32_t F_SCL, uint8_t set_interruptions) {
	// Configuracion del prescaler en 1
	TWSR = (0<<TWPS1)|(0<<TWPS0);
	// Configuracion de la frecuencia de oscilacion de SCL
	uint32_t auxTWBR;
	auxTWBR = ((((F_CPU / F_SCL) / PRESCALER) - 16 ) / 2);
	TWBR = (uint8_t)auxTWBR;
	inter = set_interruptions;
}

/*	
	Set device's own slave address to TWAR
	This is done when the device is slave
*/
void I2C_init_slave(uint8_t slave_address, uint8_t interruptions) {
	inter = interruptions;
	// Write device's own slave address to TWAR
	TWAR = (slave_address<<1);		// 7 bits de direccion
	// Clear TWINT;  get ACK; enable TWI interface; set interruptions on or off
	// The TWEA bit must be written to one to enable the acknowledgement of the
	// device’s own slave address or the general call address
	TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWEN)|(inter<<TWIE);
}

/*
	Transmit START condition. This is done by the MASTER device to start transaction
*/
uint8_t I2C_STARTcond(){
	// Clean TWCR
	//TWCR = 0;
	// Enable TWI interface; transmit a START condition; clear TWINT flag; set interruptions on or off
	//TWCR = (1<<TWEN)|(1<<TWSTA)|(1<<TWINT)|(inter<<TWIE);
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);  //@@ catedra
	// Wait for hardware action: TWINT Flag set
	while (!(TWCR &	(1<<TWINT)));
	// Check value of TWI Status Register (masked) for START condition correctly transmitted.
	if(TW_STATUS != TW_START) return 0;		// if not, device is not ready
	return 1;
}


/*
	Transmit REPEATED START condition. This is done by the MASTER device when in a read operation
	It enables the Master to switch between Slaves, Master Transmitter mode and Master Receiver 
	mode without losing control of the bus.
*/
uint8_t I2C_RESTARTcond(){
	// Clean TWCR
	//TWCR = 0;
	// Enable TWI interface; transmit a START condition; clear TWINT flag; set interruptions on or off
	TWCR = (1<<TWEN)|(1<<TWSTA)|(1<<TWINT)|(inter<<TWIE);
	// Wait for hardware action: TWINT Flag set
	while (!(TWCR &	(1<<TWINT)));
	// Check value if REPERATED START condition correctly transmitted.
	if(TW_STATUS != TW_REP_START) return 0;		// if not, device is not ready
	return 1;
}

/*
	Transmit STOP condition
*/
void I2C_STOPcond(){
	// Enable TWI interface; transmit a STOP condition; clear TWINT flag
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);//(1<<TWEN)|(1<<TWSTO)|(1<<TWINT);
	
}


/*
	Sends 8 bits on the SDA line and checks condition
	If MT, TWEA on 0 and checks for TW_MT_DATA_ACK
	If ST, TWEA on 1 and checks for TW_ST_DATA_ACK
	The TWEA bit must be written to one to enable the
	acknowledgement of the device’s own slave address
*/
uint8_t I2C_write_data(uint8_t data, uint8_t TWEA_val, uint8_t cond){
	// write data byte to TWDR
	TWDR = data;
	// Clear TWINT;  get ACK; enable TWI interface; set interruptions on or off
	TWCR = (1<<TWINT)|(TWEA_val<<TWEA)|(1<<TWEN)|(inter<<TWIE);
	// Wait for hardware action: TWINT Flag set
	while (!(TWCR &	(1<<TWINT)));
	// Check if data sent and AKC received
	if(TW_STATUS != cond) return 0;		// if not, NACK
	return 1;
}


/*
	Reads 8 bits on the SDA line and checks condition
	If MR, TWEA on 0 and checks for TW_MR_DATA_ACK
	If SR, TWEA on 1 and checks for TW_SR_DATA_ACK
	The TWEA bit must be written to one to enable the
	acknowledgement of the device’s own slave address
*/
void I2C_read_data(uint8_t TWEA_val, uint8_t cond){
	// Clear TWINT;  get ACK; enable TWI interface; set interruptions on or off
	TWCR = (1<<TWINT)|(TWEA_val<<TWEA)|(1<<TWEN)|(inter<<TWIE);
	// Wait for hardware action: TWINT Flag set
	while (!(TWCR &	(1<<TWINT)));
	// Check if data received and AKC returned -> 		// Put in buffer the value from TWDR
	if(TW_STATUS == cond){
		switch(TWDR){
			case ':':
				flagcom = 1;
				indcom = 0;
				break;
			case 0:
			case '\r':
			case '\n':
				if(flagcom){
					comando[indcom] = 0;
					indcom = 0;
					i2c_interpreter();
				}
				flagcom = 0;
				break;
			default:
				if(flagcom && indcom<comSize)	comando[indcom++] = TWDR;
				break;
		}
	}
}

/*
	Interruption service rutine
*/
ISR(TWI_vect)
{
	switch(TW_STATUS)
	{
		case TW_SR_SLA_ACK:
			I2C_read_data(TWEA_slave, TW_STATUS);
			break;
		case TW_SR_DATA_ACK:
			I2C_read_data(TWEA_slave, TW_STATUS);
			break;
		case TW_SR_STOP:
			TWCR |= (1<<TWINT);		
			break;
		case TW_ST_SLA_ACK:
			I2C_write_data(TWDR, 1, TW_STATUS);
			break;
		case TW_ST_DATA_ACK:
			I2C_write_data(TWDR, 1, TW_STATUS);
			break;
		case TW_BUS_ERROR:
			printf("ERROR!\r\n");
			// illegal start or stop condition
 			TWCR = (1 << TWIE) | (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
			break;
		default:
			break;
	}
}
