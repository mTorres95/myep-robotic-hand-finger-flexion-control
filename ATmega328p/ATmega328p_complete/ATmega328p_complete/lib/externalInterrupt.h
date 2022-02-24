/*
 * externalInterrupt.h
 *
 *  Author: miact
 */ 


#ifndef EXTERNALINTERRUPT_H_
#define EXTERNALINTERRUPT_H_

#include "main.h"

typedef enum
{	INT0_nivelBajo			= 0,
	INT0_cualquierFlanco	= 1,
	INT0_flancoBajada		= 2,
	INT0_flancoSubida		= 3,
}int0_evento; // Tipo de evento que levanta el flag de interrupciones

typedef enum
{	INT1_nivelBajo			= 0,
	INT1_cualquierFlanco	= 1,
	INT1_flancoBajada		= 2,
	INT1_flancoSubida		= 3,
}int1_evento; // Tipo de evento que levanta el flag de interrupciones

void configuracion_INT0(int0_evento evento);
void configuracion_INT1(int1_evento evento);


#endif /* EXTERNALINTERRUPT_H_ */