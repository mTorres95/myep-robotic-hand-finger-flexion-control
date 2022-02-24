/*
 * servomotors.c
 *
 *  Author: miact
 */ 

#include "servomotors.h"

// ======================= TIMER 0 =============================
void set_TC0_for_servomotors(){
	T_servo_ms = 16;								// [ms] periodo del PWM para controlar los servomotores
	configuracion_modo_timer0(FAST_PWM_8b);			// Fast PWM con 0xFF (255) como TOP
	seleccion_prescaler_ms_timer0(T_servo_ms);		// Prescaler de acuerdo al periodo requerido
	configuracion_modoSalidas_timer0(Clear, Clear);	// Salida OC0A en Clear, OC0B en Clear
}


void set_degrees_TC0(float degreesA, float degreesB){
	float dutycicleA = -1.0;
	float dutycicleB = -1.0;
	// Segun datasheet de SG90
	// -90� --> 1ms
	// +90� --> 2ms
	// Ecuacion de la recta dados dos puntos
	if(degreesA >= min_degree && degreesA <= max_degree)	dutycicleA = (1.0/180.0)*(degreesA + 90.0) + 1.0;
	if(degreesB >= min_degree && degreesB <= max_degree)	dutycicleB = (1.0/180.0)*(degreesB + 90.0) + 1.0;
	
	set_dutycicle_ms_TC0(dutycicleA, dutycicleB);
}

void get_degrees_TC0(uint8_t F1, uint8_t F2){
	printf("Funcion get_degrees_TC0 no desarrollada\r\n");
}


// ======================= TIMER 1 =============================
void set_TC1_for_servomotors(){
	T_servo_ms = 20;								// [ms] periodo del PWM para controlar los servomotores
	configuracion_modo_timer1(FAST_PWM_ICRx);		// Fast PWM con ICR1 como TOP
	seleccion_prescaler_ms_timer1(T_servo_ms);		// Prescaler de acuerdo al periodo requerido
	set_ICR1_TOP(T_servo_ms);						// Configuracion de ICR1
	configuracion_modoSalidas_timer1(Clear, Clear);	// Salida OC1A en Clear, OC1B en Clear
}

void set_degrees_TC1(float degreesA, float degreesB){
	float dutycicleA = -1.0;
	float dutycicleB = -1.0;
	// Segun datasheet de SG90
	// -90� --> 1ms
	// +90� --> 2ms
	// Ecuacion de la recta dados dos puntos
	if(degreesA >= min_degree && degreesA <= max_degree)	dutycicleA = (1.0/180.0)*(degreesA + 90.0) + 1.0;
	if(degreesB >= min_degree && degreesB <= max_degree)	dutycicleB = (1.0/180.0)*(degreesB + 90.0) + 1.0;
		
	set_dutycicle_ms_TC1(dutycicleA, dutycicleB);
}

void get_degrees_TC1(uint8_t F1, uint8_t F2){
	printf("Funcion get_degrees_TC1 no desarrollada\r\n");
}

// ======================= TIMER 2 =============================
void set_TC2_for_servomotors(){
	T_servo_ms = 16;									// [ms] periodo del PWM para controlar los servomotores
	configuracion_modo_timer2(FAST_PWM_8b);				// Fast PWM con 0xFF (255) como TOP
	seleccion_prescaler_ms_timer2(T_servo_ms);			// Prescaler de acuerdo al periodo requerido
	configuracion_modoSalidas_timer2(Clear, Disconnected);		// Salida OC2A en Clear, OC2B en Off
}



void set_degrees_TC2(float degreesA, float degreesB){
	float dutycicleA = -1.0;
	float dutycicleB = -1.0;
	// Segun datasheet de SG90
	// -90� --> 1ms
	// +90� --> 2ms
	// Ecuacion de la recta dados dos puntos
	if(degreesA >= min_degree && degreesA <= max_degree)	dutycicleA = (1.0/180.0)*(degreesA + 90.0) + 1.0;
	if(degreesB >= min_degree && degreesB <= max_degree)	dutycicleB = (1.0/180.0)*(degreesB + 90.0) + 1.0;
	
	set_dutycicle_ms_TC2(dutycicleA, dutycicleB);
}

void get_degrees_TC2(uint8_t F1, uint8_t F2){
	printf("Funcion get_degrees_TC2 no desarrollada\r\n");
}