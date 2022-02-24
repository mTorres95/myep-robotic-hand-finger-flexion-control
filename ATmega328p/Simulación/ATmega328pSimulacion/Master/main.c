/*
 * Master.c
 *
 * Author : miact
 */ 

#include "lib/main.h"

int main(void)
{
	// Configuracion de UART
	UART_init(BAUD, 1, 0);
	
	// Configuracion de I2C master
	I2C_init_master(100000,INTER_ON);
	
	sei();		// Habilitacion de interrupciones globales
	
	while (1)
	{
	}
}

