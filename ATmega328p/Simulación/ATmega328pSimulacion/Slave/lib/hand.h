/*
 * hand.h
 *
 *  Author: miact
 */ 


#ifndef HAND_H_
#define HAND_H_

#include "main.h"

// Configurable variables
float max_degree;
float min_degree;
float init_degree;

// hand control
void init_hand(float init_degree);
void hand_flexion(uint8_t flexion);
void hand_degree(float degree);
// individual finger control
void finger1_flexion(uint8_t flexion);
void finger1_degree(float degree);
void finger2_flexion(uint8_t flexion);
void finger2_degree(float degree);
void finger3_flexion(uint8_t flexion);
void finger3_degree(float degree);
void finger4_flexion(uint8_t flexion);
void finger4_degree(float degree);
void finger5_flexion(uint8_t flexion);
void finger5_degree(float degree);

#endif /* HAND_H_ */