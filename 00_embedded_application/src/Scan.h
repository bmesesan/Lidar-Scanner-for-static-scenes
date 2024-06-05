/*
 * Scan.h
 *
 * Created: 12/11/2019 1:37:31 PM
 *  Author: Bogdan
 */ 


#ifndef SCAN_H_
#define SCAN_H_

#include "Serial_Communication.h"
#include "Stepper.h"
#include "Servo_Setup.h"
#include "LIDAR_LITE_V3.h"
#include "Controller.h"

#define START_SCAN 127
#define SET_PARAMS 126
#define CONTINUE_SEND 125

//Sets the scanning parameters
 void set_params(void);

//Sets the Stepper in its correct initial position
void Scan_Set_Stepper_position(unsigned char *stepvar, int curr_pos);

//Takes a measurement from the LIDAR and the stepper motor makes a step
void Scan_Step_Measurement(unsigned char dir, unsigned char *stepvar, unsigned int *stepper_count, int current_servo_angle);

//The scanner makes a swipe scan on the X axis
 void Scan_X_Axis(unsigned int nr_steps, unsigned char *dir, unsigned char *stepvar, int *servo_angle);

//The scanner makes a full scan on both the X and Y axis
void Scan_XY(unsigned char *dir, unsigned char *stepvar);

//The scanner makes a swipe scan on the Y axis
void Scan_Y_Axis(int *servo_current_angle);

//The scanner makes a full scan on Y and X axis
void Scan_YX(unsigned char *dir, unsigned char *stepvar);

#endif /* SCAN_H_ */