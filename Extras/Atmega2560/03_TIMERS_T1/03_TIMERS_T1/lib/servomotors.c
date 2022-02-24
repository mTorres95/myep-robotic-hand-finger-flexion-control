/*
 * servomotors.c
 *
 *  Author: miact
 */ 

#include "servomotors.h"
// ========================== TC1 ==============================
void set_TC1_for_servomotors(){
	output_setting_timer1();					// Salida en OC1A, OC1B y OC1C
	T_servo_ms = 20;							// [ms] periodo del PWM para controlar los servomotores
	configuracion_modo_timer1(FAST_PWM_ICRx);	// Fast PWM con ICR1 como TOP
	seleccion_prescaler_ms_timer1(T_servo_ms);	// Prescaler de acuerdo al periodo requerido
	set_ICR1_TOP(T_servo_ms);
	configuracion_modoSalidas_timer1(2,2,2);	// Salida OC1A en Clear, OC1B en Clear, OC1C en Clear
}

void set_dutycicle_ms_TC1(float dutycicleA, float dutycicleB, float dutycicleC){
	uint16_t OCR1A_val = -1;
	uint16_t OCR1B_val = -1;
	uint16_t OCR1C_val = -1;
	if(!(dutycicleA<0)){
		OCR1A_val = (uint16_t)( (dutycicleA/1000.0)*(F_CPU/prescaler_TC1)+1 );		
	}
	if(!(dutycicleB<0)){
		OCR1B_val = (uint16_t)( (dutycicleB/1000.0)*(F_CPU/prescaler_TC1)+1 );
	}
	if(!(dutycicleC<0)){
		OCR1C_val = (uint16_t)( (dutycicleC/1000.0)*(F_CPU/prescaler_TC1)+1 );
	}
	set_OCR1(OCR1A_val, OCR1B_val, OCR1C_val);
}

void set_degrees_TC1(float degreesA, float degreesB, float degreesC){
	float dutycicleA = -1.0;
	float dutycicleB = -1.0;
	float dutycicleC = -1.0;
	// -90° --> 1ms
	// +90° --> 2ms
	// Ecuacion de la recta dados dos puntos
	if(degreesA >= -90.0 && degreesA <= 90.0)	dutycicleA = (1.0/180.0)*(degreesA + 90.0) + 1.0;
	if(degreesB >= -90.0 && degreesB <= 90.0)	dutycicleB = (1.0/180.0)*(degreesB + 90.0) + 1.0;
	if(degreesC >= -90.0 && degreesC <= 90.0)	dutycicleC = (1.0/180.0)*(degreesC + 90.0) + 1.0;
	
	set_dutycicle_ms_TC1(dutycicleA, dutycicleB, dutycicleC);
}

void get_degrees_TC1(uint8_t F1, uint8_t F2, uint8_t F3){
	printf("Funcion get_degrees_TC1 no desarrollada\r\n");
}
// ======================== END TC1 ============================

// ========================== TC3 ==============================
void set_TC3_for_servomotors(){
	output_setting_timer3();					// Salida en OC3A, OC3B y OC3C
	T_servo_ms = 20;							// [ms] periodo del PWM para controlar los servomotores
	configuracion_modo_timer3(FAST_PWM_ICRx);	// Fast PWM con ICR3 como TOP
	seleccion_prescaler_ms_timer3(T_servo_ms);	// Prescaler de acuerdo al periodo requerido
	set_ICR3_TOP(T_servo_ms);
	configuracion_modoSalidas_timer3(2,2,2);	// Salida OC3A en Clear, OC3B en Clear, OC3C en Clear
}

void set_dutycicle_ms_TC3(float dutycicleA, float dutycicleB, float dutycicleC){
	uint16_t OCR3A_val = -1;
	uint16_t OCR3B_val = -1;
	uint16_t OCR3C_val = -1;
	if(!(dutycicleA<0)){
		OCR3A_val = (uint16_t)( (dutycicleA/1000.0)*(F_CPU/prescaler_TC3)+1 );
	}
	if(!(dutycicleB<0)){
		OCR3B_val = (uint16_t)( (dutycicleB/1000.0)*(F_CPU/prescaler_TC3)+1 );
	}
	if(!(dutycicleC<0)){
		OCR3C_val = (uint16_t)( (dutycicleC/1000.0)*(F_CPU/prescaler_TC3)+1 );
	}
	set_OCR3(OCR3A_val, OCR3B_val, OCR3C_val);
}

void set_degrees_TC3(float degreesA, float degreesB, float degreesC){
	float dutycicleA = -1.0;
	float dutycicleB = -1.0;
	float dutycicleC = -1.0;
	// -90° --> 1ms
	// +90° --> 2ms
	// Ecuacion de la recta dados dos puntos
	if(degreesA >= -90.0 && degreesA <= 90.0)	dutycicleA = (1.0/180.0)*(degreesA + 90.0) + 1.0;
	if(degreesB >= -90.0 && degreesB <= 90.0)	dutycicleB = (1.0/180.0)*(degreesB + 90.0) + 1.0;
	if(degreesC >= -90.0 && degreesC <= 90.0)	dutycicleC = (1.0/180.0)*(degreesC + 90.0) + 1.0;
	
	set_dutycicle_ms_TC3(dutycicleA, dutycicleB, dutycicleC);
}

void get_degrees_TC3(uint8_t F1, uint8_t F2, uint8_t F3){
	printf("Funcion get_degrees_TC3 no desarrollada\r\n");
}
// ======================== END TC3 ============================

void homing(){
	printf("HOMING..\r\n");
	set_degrees_TC1(0.0, 0.0, 0.0);
	set_degrees_TC3(0.0, 0.0, 0.0);
}