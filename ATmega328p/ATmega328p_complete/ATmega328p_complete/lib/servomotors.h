/*
 * servomotors.h
 *
 *  Author: miact
 */ 


#ifndef SERVOMOTORS_H_
#define SERVOMOTORS_H_

#include "timers.h"

float T_servo_ms;

// ======================= TIMER 0 =============================
void set_TC0_for_servomotors();
void set_degrees_TC0(float degrees_F1, float degrees_F2);
void get_degrees_TC0(uint8_t F1, uint8_t F2);
// ======================= TIMER 1 =============================
void set_TC1_for_servomotors();
void set_degrees_TC1(float degrees_F1, float degrees_F2);
void get_degrees_TC1(uint8_t F1, uint8_t F2);
// ======================= TIMER 2 =============================
void set_TC2_for_servomotors();
void set_degrees_TC2(float degrees_F1, float degrees_F2);
void get_degrees_TC2(uint8_t F1, uint8_t F2);
// =============================================================
void homing();

#endif /* SERVOMOTORS_H_ */