/*
 * externalInterrupt.c
 *
 *  Author: miact
 */ 

#include "externalInterrupt.h"

void configuracion_INT0(int0_evento evento)
{
	// INT0 como entrada
	DDRD  &=~ (1<<DDD2);
	// Configuracion del tipo de evento que levanta el flag de interrupcion
	EICRA &=~ (3<<ISC00);
	EICRA |=  (evento<<ISC00);
	// Apagado del flag
	EIFR  |=  (1<<INTF0);
	// Habilitar interrupciones en INT0
	EIMSK |=  (1<<INT0);
}

void configuracion_INT1(int1_evento evento)
{
	// INT1 como entrada
	DDRD  &=~ (1<<DDD3);
	// Configuracion del tipo de evento que levanta el flag de interrupcion
	EICRA &=~ (3<<ISC10);
	EICRA |=  (evento<<ISC10);
	// Apagado del flag
	EIFR  |=  (1<<INTF1);
	// Habilitar interrupciones en INT0
	EIMSK |=  (1<<INT1);
}

// Rutina de servicio interrupcion externa INT0
ISR(INT0_vect)
{
	// Cómo evitar ruidos en el botón
	// 1. Leer continuamente el estado del pin y detectar el flanco (ascendente en este trabajo) que indica que se ha pulsado un botón
	// 2. Esperar un tiempo prudente (alrededor de 10 a 100 mili segundos) hasta que se estabilice la señal
	_delay_ms(50);
	// 3.Leer nuevamente el estado del pin y comprobar que se encuentre en el estado deseado
	if(!(PIND   &  (1<<PIND2))){
		// 4. Ejecutar la acción asignada al botón, una vez que nos aseguramos que efectivamente fue presionado.
		hand_degree(init_degree);
		printf("Reset\r\n");
	}
	// Apagado del flag
	EIFR  |=  (1<<INTF0);
	
}

// Rutina de interrupcion externa INT1
ISR(INT1_vect)
{	
	// Apagado del flag
	EIFR |= (1<<INTF1);
}