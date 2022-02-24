/*
 * hand.c
 *
 *  Author: miact
 */ 
#include "hand.h"

void init_hand(){
	// Configuracion de las variables configurables de la mano
	max_degree = 90.0;
	min_degree = -90.0;
	init_degree = 0.0;
	// Configuracion de los timers para los servomotores
	set_TC0_for_servomotors();
	set_TC1_for_servomotors();
	set_TC2_for_servomotors();
	// Posicion inicial
	hand_degree(init_degree);
}

void hand_flexion(uint8_t flexion){
	finger1_flexion(flexion);
	finger2_flexion(flexion);
	finger3_flexion(flexion);
	finger4_flexion(flexion);
	finger5_flexion(flexion);
}

void hand_degree(float degree){
	set_degrees_TC1(degree, degree);
	set_degrees_TC0(degree, degree);
	set_degrees_TC2(degree, -180.0);
}

float flexion_to_degree(uint8_t flexion){
	return ((max_degree - min_degree)/(100 - 0)*(flexion - 0)) + min_degree;
}

void finger1_flexion(uint8_t flexion){
	set_degrees_TC1(flexion_to_degree(flexion), -180.0);
}

void finger1_degree(float degree){
	set_degrees_TC1(degree, -180.0);	
}

void finger2_flexion(uint8_t flexion){
	set_degrees_TC1(-180.0, flexion_to_degree(flexion));
}

void finger2_degree(float degree){
	set_degrees_TC1(-180.0, degree);
}

void finger3_flexion(uint8_t flexion){
	set_degrees_TC0(flexion_to_degree(flexion), -180.0);
}

void finger3_degree(float degree){
	set_degrees_TC0(degree, -180.0);
}

void finger4_flexion(uint8_t flexion){
	set_degrees_TC0(-180.0, flexion_to_degree(flexion));
}

void finger4_degree(float degree){
	set_degrees_TC0(-180.0, degree);
}

void finger5_flexion(uint8_t flexion){
	set_degrees_TC2(flexion_to_degree(flexion), -180.0);
}

void finger5_degree(float degree){
	set_degrees_TC2(degree, -180.0);
}

