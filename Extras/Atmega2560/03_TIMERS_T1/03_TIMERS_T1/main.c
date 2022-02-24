/*
 * 03_TIMERS_T1.c
 *
 * Created: 31/01/2022 10:05:26
 * Author : miact
 */ 

#include "lib/main.h"


int main(void)
{
	// Configuracion de la UART
	UART_init(BAUD,1,0);	// Define baudrate, habilita interrupciones por Rx pero no por Tx
	
	// Configuracion de los timers para los servomotores
	// TIMER 1, 3 OUTPUTS
	printf("=== TIMER 1 ===\r\n");
	set_TC1_for_servomotors();
	// TIMER 3, 3 OUTPUTS
	printf("=== TIMER 3 ===\r\n");
	set_TC3_for_servomotors();
	
	sei();		// Habilitacion de interrupciones globales
	
	homing();
	help();		// Muestra la guia de los comandos
	
    while (1) 
    {
    }
}

