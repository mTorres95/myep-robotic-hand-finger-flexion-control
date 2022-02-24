/*
 * Slave.c
 *
 * Author : miact
 */ 

#include "lib/main.h"

int main(void)
{
	// Configuracion de las interrupciones externas INT0
	configuracion_INT0(INT0_flancoSubida);
	
	// Configuracion de la UART
	UART_init(BAUD,1,0);	// Define baudrate, habilita interrupciones por Rx pero no por Tx
	
	// Configuracion de I2C slave
	I2C_init_slave(SLA, INTER_ON);
	
	// Iniciar mano en posicion inicial
	init_hand(init_degree);
	
	sei();		// Habilitacion de interrupciones globales
	
	help();		// Muestra la guia de los comandos
	while (1) {
		
	}
	
}

