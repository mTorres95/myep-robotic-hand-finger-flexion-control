/*
 * main.h
 *
 *  Author: miact
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 16000000
#define BAUD 9600

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>			// para la funcion pow en timers
#include <util/delay.h>
#include "uart.h"
#include "i2c.h"
#include "i2c_sendInstructions.h"


#endif /* MAIN_H_ */