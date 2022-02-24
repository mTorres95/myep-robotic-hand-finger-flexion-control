/*
 * i2c_interpreter.c
 *
 *  Author: miact
 */ 

#include "i2c_interpreter.h"

uint8_t getVal(uint8_t ind){
	// UINT8_MAX -> 255 (3 cifras)
	// Ademas, el servidor envia valores del 0 a 100
	uint8_t val = 0;
	for(int i=(ind+1); i<=(ind+4); i++){
		indcom = i;
		if(!isdigit(comando[i]))	break;
		val = val*10 + comando[i] - '0';
	}
	return val;
}


void i2c_interpreter(){
	switch(comando[indcom]){
		case 'A':						
			printf("Dedo 1 ");
			ff1 = getVal(indcom);
			printf("-> %d\r\n", ff1);
			i2c_interpreter();
			break;
		case 'B':						
			printf("Dedo 2 ");
			ff2 = getVal(indcom);
			printf("-> %d\r\n", ff2);
			i2c_interpreter();
			break;
		case 'C':						
			printf("Dedo 3 ");
			ff3 = getVal(indcom);
			printf("-> %d\r\n", ff3);
			i2c_interpreter();
			break;
		case 'D':						
			printf("Dedo 4 ");
			ff4 = getVal(indcom);
			printf("-> %d\r\n", ff4);
			i2c_interpreter();
			break;
		case 'E':						
			printf("Dedo 5 ");
			ff5 = getVal(indcom);
			printf("-> %d\r\n", ff5);
			i2c_interpreter();
			break;
		case 0:
			finger1_flexion(ff1);
			finger2_flexion(ff2);
			finger3_flexion(ff3);
			finger4_flexion(ff4);
			finger5_flexion(ff5);
			break;
		default:
			printf("\r\nError de recepcion\r\n");
			break;
	}
}