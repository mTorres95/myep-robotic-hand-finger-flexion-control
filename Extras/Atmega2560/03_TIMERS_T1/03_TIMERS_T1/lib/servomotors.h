/*
 * servomotors.h
 *
 *  Author: miact
 */ 


#ifndef SERVOMOTORS_H_
#define SERVOMOTORS_H_

#include "timers.h"

float T_servo_ms;

// ================================ TC1 =====================================
void set_TC1_for_servomotors();
void set_dutycicle_ms_TC1(float dutycicle1A, float dutycicle1B, float dutycicle1C);
void set_degrees_TC1(float degrees_F1, float degrees_F2, float degrees_F3);
void get_degrees_TC1(uint8_t F1, uint8_t F2, uint8_t F3);

// ================================ TC3 ====================================
void set_TC3_for_servomotors();
void set_dutycicle_ms_TC3(float dutycicle3A, float dutycicle3B, float dutycicle3C);
void set_degrees_TC3(float degrees_F4, float degrees_F5, float degrees_F6);
void get_degrees_TC3(uint8_t F4, uint8_t F5, uint8_t F6);

void homing();

#endif /* SERVOMOTORS_H_ */