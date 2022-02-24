/*
 * i2c_interpreter.h
 *
 *  Author: miact
 */ 


#ifndef I2C_INTERPRETER_H_
#define I2C_INTERPRETER_H_

#include "main.h"

// Variables to save the data in a buffer to send to the interpreter
uint8_t flagcom;			// flag of initiated command
uint8_t indcom;				// index of reception buffer
#define comSize 30			// reception buffer size
char comando[comSize];		// reception buffer

// Variables to save finger flexion data, received from server
// uint8_t because flexion goes from 0 to 100 (UINT8_MAX is 255)
uint8_t ff1;
uint8_t ff2;
uint8_t ff3;
uint8_t ff4;
uint8_t ff5;


void get_command(uint8_t data);
void i2c_interpreter();


#endif /* I2C_INTERPRETER_H_ */