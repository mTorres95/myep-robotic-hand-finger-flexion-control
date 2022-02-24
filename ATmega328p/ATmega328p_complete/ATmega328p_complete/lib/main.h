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
#include <ctype.h>			// funcion isdigit()
#include <math.h>			// para la funcion pow en timers
#include <util/delay.h>
#include "externalInterrupt.h"
#include "uart.h"
#include "uartInterpreter.h"
#include "servomotors.h"
#include "i2c.h"
#include "i2c_interpreter.h"
#include "hand.h"


#endif /* MAIN_H_ */