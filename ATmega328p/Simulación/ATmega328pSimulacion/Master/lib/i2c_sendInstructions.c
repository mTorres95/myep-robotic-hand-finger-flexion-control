/*
 * i2c_sendInstructions.c
 *
 *  Author: miact
 */ 

#include "main.h"

// Nota: TWEA_master 0 -> Master no necesita enviar ACK

void send_instruction(char comando[]){
	// Envio de la condicion de START
	I2C_STARTcond();
	
	// Envio de la direccion del slave
	uint8_t sla_add;
	sla_add = (SLA << 1);	// 7 bits de direccion
	sla_add &=~ 1;					// W -> 8vo bit en '0'
	I2C_write_data(sla_add, TWEA_master, TW_MT_SLA_ACK);
	
	// Envio del registro del slave
	uint8_t sla_TWDR = 0xBB;			// posicion en memoria del registro TWDR de un ATmega328p
	I2C_write_data(sla_TWDR, TWEA_master, TW_MT_DATA_ACK);
	
	// Envio de datos
	for(int i=0; i<comSize; i++){
		I2C_write_data(comando[i], TWEA_master, TW_MT_DATA_ACK);
		if(comando[i] == 0) break;
		_delay_us(2);
		//printf("Envia %c\r\n", comando[i]);
	}
	
	// Envio de la condicion de STOP
	I2C_STOPcond();
}
