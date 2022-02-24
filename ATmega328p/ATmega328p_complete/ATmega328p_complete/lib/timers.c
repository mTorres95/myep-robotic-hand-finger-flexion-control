/*
 * timers.c
 *
 *  Author: miact
 */ 
#include "timers.h"

// ======================= TIMER 0 =============================
void configuracion_modo_timer0(uint8_t modo){
	printf("TIMER 0 - Mode: %d\r\n", modo);
	// Resetear a 0 los bits de configuracion de modo
	TCCR0A &=~ (3<<WGM00);  // 3 -> 0b11
	TCCR0B &=~ (1<<WGM02);
	
	switch(modo){
		case 0: // 0 0 0
			break;
		case 1: // 0 0 1
			TCCR0A |=  (1<<WGM00);
			break;
		case 2: // 0 1 0
			TCCR0A |=  (1<<WGM01);
			break;
		case 3: // 0 1 1
			TCCR0A |=  (3<<WGM00);
			break;
		case 5: // 1 0 1
			TCCR0A |=  (1<<WGM00);
			TCCR0B |=  (1<<WGM02);
			break;
		case 7: // 1 1 1
			TCCR0A |=  (3<<WGM00);
			TCCR0B |=  (1<<WGM02);
			break;
		default:
			printf("Invalid mode\r\n");
			break;
	}
}

void configuracion_prescaler_timer0(uint16_t prescaler){
	printf("Prescaler: %d\r\n", prescaler);
	// Resetear a 0 los bits de configuracion del prescaler
	TCCR0B &=~ (7<<CS00);  // 7 -> 0b111
	
	switch(prescaler){
		case 0:
			printf("Timer 0 OFF\r\n");
			break;
		case 1:			// 0 0 1
			TCCR0B |= (1<<CS00);
			break;
		case 8:			// 0 1 0
			TCCR0B |= (1<<CS01);
			break;
		case 64:		// 0 1 1
			TCCR0B |= (3<<CS00);
			break;
		case 256:		// 1 0 0
			TCCR0B |= (1<<CS02);
			break;
		case 1024:		// 1 0 1
			TCCR0B |= (1<<CS00)|(1<<CS02);
			break;
		default:
			printf("Invalid prescaler. Can't initialize TIMER 0\r\n");
			break;
	}
}

void seleccion_prescaler_ms_timer0(float T){		//[ms]
	prescaler_TC0 = 0;
	T = T/1000.0;									// pasa a [seg]
	float aux = (float)(1.0*(pow(2, 8)/F_CPU));			// tiempo maximo con prescaler=1 para Timer de 8 bits
	if		(T <=      aux) prescaler_TC0 = 1;
	else if (T <=    8*aux) prescaler_TC0 = 8;
	else if (T <=   64*aux) prescaler_TC0 = 64;
	else if (T <=  256*aux) prescaler_TC0 = 256;
	else if (T <= 1024*aux) prescaler_TC0 = 1024;
	else printf("Time out of range!\r\n");
	
	configuracion_prescaler_timer0(prescaler_TC0);
}

void  configuracion_modoSalidas_timer0(uint8_t outA, uint8_t outB){
	// Resetear a 0 los bits de configuracion de los modos de salida
	TCCR0A &=~ (3<<COM0A0)|(3<<COM0B0);
	// Apagar las salidas OC0A y OC0B
	DDRD &=~ (1<<DDD6)|(1<<DDD5);		// Salida en OC0A y OC0B
	
	switch(outA){
		case 0: // 0 0
			printf("OC0A Off\r\n");
			break;
		case 1: // 0 1
			printf("OC0A Toggle\r\n");
			DDRD   |= (1<<DDD6);		// Salida en OC0A
			TCCR0A |= (1<<COM0A0);
			break;
		case 2: // 1 0
			printf("OC0A Clear\r\n");
			DDRD   |= (1<<DDD6);		// Salida en OC0A
			TCCR0A |= (2<<COM0A0);
			break;
		case 3: // 1 1
			printf("OC0A Set\r\n");
			DDRD   |= (1<<DDD6);		// Salida en OC0A
			TCCR0A |= (3<<COM0A0);
			break;
		default:
			printf("Invalid output mode for OC0A\r\n");
			break;
	}
	
	switch(outB){
		case 0: // 0 0
			printf("OC0B Off\r\n\r\n");
			break;
		case 1: // 0 1
			printf("OC0B Toggle\r\n\r\n");
			DDRD   |= (1<<DDD5);		// Salida en OC0B
			TCCR0A |= (1<<COM0B0);
			break;
		case 2: // 1 0
			printf("OC0B Clear\r\n\r\n");
			DDRD   |= (1<<DDD5);		// Salida en OC0B
			TCCR0A |= (2<<COM0B0);
			break;
		case 3: // 1 1
			printf("OC0B Set\r\n\r\n");
			DDRD   |= (1<<DDD5);		// Salida en OC0B
			TCCR0A |= (3<<COM0B0);
			break;
		default:
			printf("Invalid output mode for OC0B\r\n\r\n");
			break;
	}
}

void configuracion_interrupciones_timer0(uint8_t outputCaptA,
										 uint8_t outputCaptB, 
										 uint8_t overflow){
	// Output Compare Match A
	if(outputCaptA){
		TIFR0  |= (1<<OCF0A);	// apaga el flag (se apagan con 1)
		TIMSK0 |= (1<<OCIE0A);	// habilita la interrupcion
	}
	// Output Compare Match B
	if(outputCaptB){
		TIFR0  |= (1<<OCF0B);	// apaga el flag (se apagan con 1)
		TIMSK0 |= (1<<OCIE0B);	// habilita la interrupcion
	}
	// Overflow
	if(overflow){
		TIFR0  |= (1<<TOV0);	// apaga el flag (se apagan con 1)
		TIMSK0 |= (1<<TOIE0);	// habilita la interrupcion
	}
}

void set_OCR0(uint8_t OCR0A_val, uint8_t OCR0B_val){
	if((OCR0A_val<(uint8_t)(UINT8_MAX)))	OCR0A = OCR0A_val;
	if((OCR0B_val<(uint8_t)(UINT8_MAX)))	OCR0B = OCR0B_val;
}

/*
	Este timer al tener solo 8 bits, tiene menor resolucion que un timer de 16 bits
	En lugar de calcular los valores de OCR0x con:
	(dutycicleA/1000.0)*(F_CPU/prescaler_TC0)+1
	se calcula mediante la ecuacion de la recta dados dos puntos,
	sabiendo que:
	
	Angulo deseado    |      dutycicle		|    OCR0x
		-90			  |		   1ms			|     14
		 90			  |		   2ms			|     31
*/
void set_dutycicle_ms_TC0(float dutycicleA, float dutycicleB){
	uint8_t OCR0A_val = -1;
	uint8_t OCR0B_val = -1;
	if(!(dutycicleA<0)){
		// OCR0A_val = (uint8_t)( (dutycicleA/1000.0)*(F_CPU/prescaler_TC0)+1 );
		OCR0A_val = (uint8_t)((17.0/1.0)*(dutycicleA - 1.0) + 14.0);
	}
	if(!(dutycicleB<0)){
		// OCR0B_val = (uint8_t)( (dutycicleB/1000.0)*(F_CPU/prescaler_TC0)+1 );
		OCR0B_val = (uint8_t)((17.0/1.0)*(dutycicleB - 1.0) + 14.0);
	}
	set_OCR0(OCR0A_val, OCR0B_val);
}
// ====================== END TIMER 0 ==========================

// ======================= TIMER 1 =============================
void configuracion_modo_timer1(uint8_t modo){
	printf("TIMER 1 - Mode: %d\r\n", modo);
	// Resetear a 0 los bits de configuracion de modo
	TCCR1A &=~ (3<<WGM10);  // 3 -> 0b11
	TCCR1B &=~ (3<<WGM12);
	
	switch(modo){
		case 0: // 0 0 0 0
			break;
		case 1: // 0 0 0 1
			TCCR1A |=  (1<<WGM10);
			break;
		case 2: // 0 0 1 0
			TCCR1A |=  (1<<WGM11);
			break;
		case 3: // 0 0 1 1
			TCCR1A |=  (3<<WGM10);
			break;
		case 4: // 0 1 0 0
			TCCR1B |=  (1<<WGM12);
			break;
		case 5: // 0 1 0 1
			TCCR1A |=  (1<<WGM10);
			TCCR1B |=  (1<<WGM12);
			break;
		case 6: // 0 1 1 0
			TCCR1A |=  (1<<WGM11);
			TCCR1B |=  (1<<WGM12);
			break;
		case 7: // 0 1 1 1
			TCCR1A |=  (3<<WGM10);
			TCCR1B |=  (1<<WGM12);
			break;
		case 8: // 1 0 0 0
			TCCR1B |=  (1<<WGM13);
			break;
		case 9: // 1 0 0 1
			TCCR1A |=  (1<<WGM10);
			TCCR1B |=  (1<<WGM13);
			break;
		case 10: // 1 0 1 0
			TCCR1A |=  (1<<WGM11);
			TCCR1B |=  (1<<WGM13);
			break;
		case 11: // 1 0 1 1
			TCCR1A |=  (3<<WGM10);
			TCCR1B |=  (1<<WGM13);
			break;
		case 12: // 1 1 0 0
			TCCR1B |=  (3<<WGM12);
			break;
		case 14: // 1 1 1 0
			TCCR1A |=  (1<<WGM11);
			TCCR1B |=  (3<<WGM12);
			break;
		case 15: // 1 1 1 1
			TCCR1A |=  (3<<WGM10);
			TCCR1B |=  (3<<WGM12);
			break;
		default:
			printf("Invalid mode\r\n");
			break;	
	}
}


void configuracion_prescaler_timer1(uint16_t prescaler){
	printf("Prescaler: %d\r\n", prescaler);
	// Resetear a 0 los bits de configuracion del prescaler
	TCCR1B &=~ (7<<CS10);  // 7 -> 0b111
	
	switch(prescaler){
		case 0:
			printf("Timer 1 OFF\r\n");
			break;
		case 1:			// 0 0 1
			TCCR1B |= (1<<CS10);
			break;
		case 8:			// 0 1 0
			TCCR1B |= (1<<CS11);
			break;
		case 64:		// 0 1 1
			TCCR1B |= (3<<CS10);
			break;
		case 256:		// 1 0 0
			TCCR1B |= (1<<CS12);
			break;
		case 1024:		// 1 0 1
			TCCR1B |= (1<<CS10)|(1<<CS12);
			break;
		default:
			printf("Invalid prescaler. Can't initialize TIMER 1\r\n");
			break;	
	}
}


void seleccion_prescaler_ms_timer1(float T){		//[ms]
	prescaler_TC1 = 0;
	T = T/1000.0;									// pasa a [seg]
	float aux = (float)(pow(2, 16)/F_CPU);			// tiempo maximo con prescaler=1 para Timer de 16 bits
	if		(T <=      aux) prescaler_TC1 = 1;
	else if (T <=    8*aux) prescaler_TC1 = 8;
	else if (T <=   64*aux) prescaler_TC1 = 64;
	else if (T <=  256*aux) prescaler_TC1 = 256;
	else if (T <= 1024*aux) prescaler_TC1 = 1024;
	else printf("Time out of range!\r\n");
	
	configuracion_prescaler_timer1(prescaler_TC1);
}


void  configuracion_modoSalidas_timer1(uint8_t outA, uint8_t outB){
	// Resetear a 0 los bits de configuracion de los modos de salida
	TCCR1A &=~ (3<<COM1A0)|(3<<COM1B0);
	// Apagar las salidas OC1A y OC1B
	DDRB &=~ (1<<DDB1)|(1<<DDB2);		// Salida en OC1A y OC1B
	
	switch(outA){
		case 0: // 0 0
			printf("OC1A Off\r\n");
			break;
		case 1: // 0 1
			printf("OC1A Toggle\r\n");
			DDRB |= (1<<DDB1);			// Salida en OC1A
			TCCR1A |= (1<<COM1A0);
			break;
		case 2: // 1 0
			printf("OC1A Clear\r\n");
			DDRB |= (1<<DDB1);			// Salida en OC1A
			TCCR1A |= (2<<COM1A0);
			break;
		case 3: // 1 1
			printf("OC1A Set\r\n");
			DDRB |= (1<<DDB1);			// Salida en OC1A
			TCCR1A |= (3<<COM1A0);
			break;
		default:
			printf("Invalid output for OC1A\r\n");
			break;	
	}
	
	switch(outB){
		case 0: // 0 0
			printf("OC1B Off\r\n\r\n");
			break;
		case 1: // 0 1
			printf("OC1B Toggle\r\n\r\n");
			DDRB   |= (1<<DDB2);			// Salida en OC2A
			TCCR1A |= (1<<COM1B0);
			break;
		case 2: // 1 0
			printf("OC1B Clear\r\n\r\n");
			DDRB   |= (1<<DDB2);			// Salida en OC2A
			TCCR1A |= (2<<COM1B0);
			break;
		case 3: // 1 1
			printf("OC1B Set\r\n\r\n");
			DDRB   |= (1<<DDB2);			// Salida en OC2A
			TCCR1A |= (3<<COM1B0);
			break;
		default:
			printf("Invalid output for OC1B\r\n");
			break;
	}
	
}


void configuracion_interrupciones_timer1(uint8_t inputCapt, uint8_t outputCaptA,
										 uint8_t outputCaptB, uint8_t overflow){
	// Input Capture
	if(inputCapt){
		TIFR1  |= (1<<ICF1);	// apaga el flag (se apagan con 1)
		TIMSK1 |= (1<<ICIE1);	// habilita la interrupcion
	}
	// Output Compare Match A
	if(outputCaptA){
		TIFR1  |= (1<<OCF1A);	// apaga el flag (se apagan con 1)
		TIMSK1 |= (1<<OCIE1A);	// habilita la interrupcion
	}
	// Output Compare Match B
	if(outputCaptB){
		TIFR1  |= (1<<OCF1B);	// apaga el flag (se apagan con 1)
		TIMSK1 |= (1<<OCIE1B);	// habilita la interrupcion
	}
	// Overflow
	if(overflow){
		TIFR1  |= (1<<TOV1);	// apaga el flag (se apagan con 1)
		TIMSK1 |= (1<<TOIE1);	// habilita la interrupcion
	}
}

void set_ICR1_TOP(float period_ms){
	ICR1 = (uint16_t)( ((period_ms/1000.0)*(F_CPU/prescaler_TC1))+1 );
}

void set_OCR1(uint16_t OCR1A_val, uint16_t OCR1B_val){
	if((OCR1A_val<(uint16_t)(UINT16_MAX)))	OCR1A = OCR1A_val;
	if((OCR1B_val<(uint16_t)(UINT16_MAX)))	OCR1B = OCR1B_val;
}

void set_dutycicle_ms_TC1(float dutycicleA, float dutycicleB){
	uint16_t OCR1A_val = -1;
	uint16_t OCR1B_val = -1;
	if(!(dutycicleA<0)){
		OCR1A_val = (uint16_t)( (dutycicleA/1000.0)*(F_CPU/prescaler_TC1)+1 );
	}
	if(!(dutycicleB<0)){
		OCR1B_val = (uint16_t)( (dutycicleB/1000.0)*(F_CPU/prescaler_TC1)+1 );
	}
	set_OCR1(OCR1A_val, OCR1B_val);
}

// ====================== END TIMER 1 ==========================

// ======================= TIMER 2 =============================
void configuracion_modo_timer2(uint8_t modo){
	printf("TIMER 2 - Mode %d\r\n", modo);
	// Resetear a 0 los bits de configuracion de modo
	TCCR2A &=~ (3<<WGM20);  // 3 -> 0b11
	TCCR2B &=~ (1<<WGM22);
	
	switch(modo){
		case 0: // 0 0 0
			break;
		case 1: // 0 0 1
			TCCR2A |=  (1<<WGM20);
			break;
		case 2: // 0 1 0
			TCCR2A |=  (1<<WGM21);
			break;
		case 3: // 0 1 1
			TCCR2A |=  (3<<WGM20);
			break;
		case 5: // 1 0 1
			TCCR2A |=  (1<<WGM20);
			TCCR2B |=  (1<<WGM22);
			break;
		case 7: // 1 1 1
			TCCR2A |=  (3<<WGM20);
			TCCR2B |=  (1<<WGM22);
			break;
		default:
			printf("Invalid mode\r\n");
			break;
	}
}

void configuracion_prescaler_timer2(uint16_t prescaler){
	printf("Prescaler: %d\r\n", prescaler);
	// Resetear a 0 los bits de configuracion del prescaler
	TCCR2B &=~ (7<<CS20);  // 7 -> 0b111
	
	switch(prescaler){
		case 0:
			printf("Timer 2 apagado\r\n");
			break;
		case 1:			// 0 0 1
			TCCR2B |= (1<<CS20);
			break;
		case 8:			// 0 1 0
			TCCR2B |= (2<<CS20);
			break;
		case 32:		// 0 1 1
			TCCR2B |= (3<<CS20);
			break;
		case 64:		// 1 0 0
			TCCR2B |= (4<<CS20);
			break;
		case 128:		// 1 0 1
			TCCR2B |= (5<<CS20);
			break;
		case 256:		// 1 1 0
			TCCR2B |= (6<<CS20);
			break;
		case 1024:		// 1 1 1
			TCCR2B |= (7<<CS20);
			break;
		default:
			printf("Invalid prescaler. Can't initialize TIMER 2\r\n");
			break;
	}
}

void seleccion_prescaler_ms_timer2(float T){	//[ms]
	prescaler_TC2 = 0;
	T = T/1000.0;		// pasa a [seg]
	float aux = (float)(pow(2, 8)/F_CPU);	// tiempo maximo con prescaler=1 para Timer de 8 bits
	if		(T <=      aux) prescaler_TC2 = 1;
	else if (T <=    8*aux) prescaler_TC2 = 8;
	else if (T <=   32*aux) prescaler_TC2 = 32;
	else if (T <=   64*aux) prescaler_TC2 = 64;
	else if (T <=  128*aux) prescaler_TC2 = 128;
	else if (T <=  256*aux) prescaler_TC2 = 256;
	else if (T <= 1024*aux) prescaler_TC2 = 1024;
	else printf("Time out of range!\r\n");
	
	configuracion_prescaler_timer2(prescaler_TC2);
}

void  configuracion_modoSalidas_timer2(uint8_t outA, uint8_t outB){
	// Resetear a 0 los bits de configuracion de los modos de salida
	TCCR2A &=~ (3<<COM2A0)|(3<<COM2B0);
	// Apagar las salidas OC2A y OC2B
	DDRB &=~ (1<<DDB3);		// Salida en OC2A
	DDRD &=~ (1<<DDD3);		// Salida en OC2B
	
	switch(outA){
		case 0: // 0 0
			printf("OC2A Off\r\n");
			break;
		case 1: // 0 1
			printf("OC2A Toggle\r\n");
			DDRB   |= (1<<DDB3);		// Salida en OC2A
			TCCR2A |= (1<<COM2A0);
			break;
		case 2: // 1 0
			printf("OC2A Clear\r\n");
			DDRB   |= (1<<DDB3);		// Salida en OC2A
			TCCR2A |= (2<<COM2A0);
			break;
		case 3: // 1 1
			printf("OC2A Set\r\n");
			DDRB   |= (1<<DDB3);		// Salida en OC2A
			TCCR2A |= (3<<COM2A0);
			break;
		default:
			printf("Invalid output for OC2A\r\n");
			break;
	}
	
	switch(outB){
		case 0: // 0 0
			printf("OC2B Off\r\n\r\n");
			break;
		case 1: // 0 1
			printf("OC2B Toggle\r\n\r\n");
			DDRD   |= (1<<DDD3);		// Salida en OC2B
			TCCR2A |= (1<<COM2B0);
			break;
		case 2: // 1 0
			printf("OC2B Clear\r\n\r\n");
			DDRD   |= (1<<DDD3);		// Salida en OC2B
			TCCR2A |= (2<<COM2B0);
			break;
		case 3: // 1 1
			printf("OC2B Set\r\n\r\n");
			DDRD   |= (1<<DDD3);		// Salida en OC2B
			TCCR2A |= (3<<COM2B0);
			break;
		default:
			printf("Invalid output for OC2B\r\n\r\n");
			break;
	}
}

void configuracion_interrupciones_timer2(uint8_t outputCaptA,
										 uint8_t outputCaptB,
										 uint8_t overflow){
	// Output Compare Match A
	if(outputCaptA){
		TIFR2  |= (1<<OCF2A);	// apaga el flag (se apagan con 1)
		TIMSK2 |= (1<<OCIE2A);	// habilita la interrupcion
	}
	// Output Compare Match B
	if(outputCaptB){
		TIFR2  |= (1<<OCF2B);	// apaga el flag (se apagan con 1)
		TIMSK2 |= (1<<OCIE2B);	// habilita la interrupcion
	}
	// Overflow
	if(overflow){
		TIFR2  |= (1<<TOV2);	// apaga el flag (se apagan con 1)
		TIMSK2 |= (1<<TOIE2);	// habilita la interrupcion
	}
}

void set_OCR2(uint8_t OCR2A_val, uint8_t OCR2B_val){
	if((OCR2A_val<(uint8_t)(UINT8_MAX)))	OCR2A = OCR2A_val;
	if((OCR2B_val<(uint8_t)(UINT8_MAX)))	OCR2B = OCR2B_val;
}

/*
	Este timer al tener solo 8 bits, tiene menor resolucion que un timer de 16 bits
	En lugar de calcular los valores de OCR0x con:
	(dutycicleA/1000.0)*(F_CPU/prescaler_TC0)+1
	se calcula mediante la ecuacion de la recta dados dos puntos,
	sabiendo que:
	
	Angulo deseado    |      dutycicle		|    OCR0x
		-90			  |		   1ms			|     14
		 90			  |		   2ms			|     31
*/
void set_dutycicle_ms_TC2(float dutycicleA, float dutycicleB){
	uint8_t OCR2A_val = -1;
	uint8_t OCR2B_val = -1;
	if(!(dutycicleA<0)){
		// OCR2A_val = (uint8_t)( (dutycicleA/1000.0)*(F_CPU/prescaler_TC2)+1 );
		OCR2A_val = (uint8_t)((17.0/1.0)*(dutycicleA - 1.0) + 14.0);	
	}
	if(!(dutycicleB<0)){
		// OCR2B_val = (uint8_t)( (dutycicleB/1000.0)*(F_CPU/prescaler_TC2)+1 );
		OCR2B_val = (uint8_t)((17.0/1.0)*(dutycicleB - 1.0) + 14.0);
	}
	set_OCR2(OCR2A_val, OCR2B_val);
}
// ====================== END TIMER 2 ==========================