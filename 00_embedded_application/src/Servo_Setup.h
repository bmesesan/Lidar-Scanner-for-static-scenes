/*
 * Servo_Setup.h
 *
 * Created: 11/13/2019 3:22:15 PM
 *  Author: Bogdan
 */ 


#ifndef SERVO_SETUP_H_
#define SERVO_SETUP_H_

#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include "MPU6050.h"

#define SERVO_STEP_COUNT 8
#define SERVO_STEP_DURATION 120
#define SERVO_STEP_DUTY_1 1380
#define SERVO_STEP_DUTY_2 1560
#define SERVO_STOP 1500

//Sets up timer1 in Phase Correct PWM mode in order to generate a signal with T = 20 ms
//Output signal is at PB2 or Pin 10 on Arduino
void Setup_Timer1_PC_PWM(void);

void Start_Timer1(void);

void Stop_Timer1(void);

//Sets the duty cycle in ms of the output signal
void Set_Timer1_duty(unsigned int duty);

//sets up the timers, ports and interrupts for correct Servo operation
void Servo_setup(void);

//Set 1000 for clock wise rotation, 1500 for stop, 2000 for Counter Clockwise rotation
void Servo_set_rotation(unsigned int duty);

#endif /* SERVO_SETUP_H_ */