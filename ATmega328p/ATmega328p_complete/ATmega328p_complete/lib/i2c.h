/*
 * i2c.h
 *
 *  Author: miact
 */ 


#ifndef I2C_H_
#define I2C_H_

#include "main.h"
#include <util/twi.h>	// State definitions, useful when reading TWSR7:3

// NOTA: I2C en AVR es TWI

// == Transmission Modes == //			Datasheet ATmega3228p, section 22.7
// (MT) Master transmitter
// (MR) Master receiver
// (ST) Slave transmitter
// (SR) Slave receiver
enum modes{MT, MR, ST, SR};
volatile enum modes mode; 

uint8_t inter;	// Used to set interruptions on or off

#define INTER_ON 1
#define INTER_OFF 0
#define TWEA_slave 1
#define TWEA_master 0
#define PRESCALER 1
#define SLA	0x20    // Slave address

void	I2C_init_master(uint32_t bitPerSecond, uint8_t interruptions);
void	I2C_init_slave(uint8_t slave_address, uint8_t interruptions);
uint8_t I2C_STARTcond();
uint8_t I2C_RESTARTcond();
void	I2C_STOPcond();
uint8_t	I2C_write_data(uint8_t data, uint8_t TWEA_val, uint8_t cond);
void	I2C_read_data(uint8_t TWEA_val, uint8_t cond);

#endif /* I2C_H_ */