/*
 * timers.h
 *
 *  Author: miact
 */ 

// Para ATMega328p, que cuenta con 2 timers de 8 bits (TIMER O y TIMER 2)
// y un timer de 16 bits (TIMER 1). Los 3 timers cuentan con prescaler y
// modo de Comparacion. El Timer 1 trae ademas modo de Captura

#ifndef TIMERS_H_
#define TIMERS_H_

#include "main.h"

typedef enum
{	Normal8			= 0,
	PWM_PC_8b		= 1,
	CTC_OCRA		= 2,
	FAST_PWM_8b		= 3,
	PWM_PC_OCR		= 5,
	FAST_PWM_OCR	= 7
}Timer8b_modo; // Tipo modos de trabajo para timers de 8 bits


typedef enum
{	
	Normal16		= 0,
	PWM_PCx_8b		= 1,
	PWM_PCx_9b		= 2,
	PWM_PCx_10b		= 3,
	CTC_OCR1A		= 4,
	FAST_PWMx_8b	= 5,
	FAST_PWMx_9b	= 6,
	FAST_PWMx_10b	= 7,
	PWM_PyFC_ICRx	= 8,
	PWM_PyFC_OCRxA	= 9,
	PWM_PC_ICRx		= 10,
	PWM_PC_OCRxA	= 11,
	CTC_ICRx		= 12,
	FAST_PWM_ICRx	= 14,
	FAST_PWM_OCRxA	= 15
}Timer16b_modo; // Tipo modos de trabajo para timers de 16 bits

typedef enum
{
	Disconnected	= 0,
	Toogle			= 1,
	Clear			= 2,
	Set				= 3
}CompareOutputMode; // Tipo modos de trabajo para timers de 16 bits


// Funciones y variables del timer 0 (8 bits)
uint16_t prescaler_TC0;
void output_setting_timer0();
void configuracion_modo_timer0(Timer8b_modo modo_0a7);
void configuracion_prescaler_timer0(uint16_t prescaler);
void seleccion_prescaler_ms_timer0(float ms);
void configuracion_modoSalidas_timer0(CompareOutputMode outA, CompareOutputMode outB);
void configuracion_interrupciones_timer0(uint8_t outputCaptA, uint8_t outputCaptB, uint8_t overflow);
void set_OCR0(uint8_t OCR0A_val, uint8_t OCR0B_val);
void set_dutycicle_ms_TC0(float dutycicleA, float dutycicleB);

// Funciones y variables del timer 1 (16 bits)
uint16_t prescaler_TC1;
void output_setting_timer1();
void configuracion_modo_timer1(Timer16b_modo modo_0a14);
void configuracion_prescaler_timer1(uint16_t prescaler);
void seleccion_prescaler_ms_timer1(float ms);
void configuracion_modoSalidas_timer1(CompareOutputMode outA, CompareOutputMode outB);
void configuracion_interrupciones_timer1(uint8_t inputCapt, uint8_t outputCaptA, uint8_t outputCaptB, uint8_t overflow);
void set_ICR1_TOP(float period_ms);
void set_OCR1(uint16_t OCR1A_val, uint16_t OCR1B_val);
void set_dutycicle_ms_TC1(float dutycicleA, float dutycicleB);


// Funciones y variables del timer 2 (8 bits)
uint16_t prescaler_TC2;
void output_setting_timer2();
void configuracion_modo_timer2(Timer8b_modo modo_0a7);
void configuracion_prescaler_timer2(uint16_t prescaler);
void seleccion_prescaler_ms_timer2(float ms);
void configuracion_modoSalidas_timer2(CompareOutputMode outA, CompareOutputMode outB);
void configuracion_interrupciones_timer2(uint8_t outputCaptA, uint8_t outputCaptB, uint8_t overflow);
void set_OCR2(uint8_t OCR2A_val, uint8_t OCR2B_val);
void set_dutycicle_ms_TC2(float dutycicleA, float dutycicleB);

#endif /* TIMERS_H_ */