/*
 * Controller.h
 *
 * Created: 4/1/2020 3:46:15 PM
 *  Author: Bogdan
 */ 


#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "Serial_Communication.h"
#include "MPU6050.h"
#include "Servo_Setup.h"

#define MAX_DELAY 300
#define KP 17
#define IMAX_LIM 5
#define IERROR_LIM (double)(20 / KI)
#define KI 3
#define KD 1
#define ERROR_DIM 3
#define NR_MEASUREMENTS 10

void setupTimer0(void);
void startTimer0(void);
void stopTimer0(void);

int getError(int sp, int pv);
int getPdelay(int error);
int getPIDdelay(int error, int prev_error, double *errorI);
void Servo_Step_New(int delay_time);

void insertError(int error_buff[], int error, unsigned int *pos);
void initBuff(int error_buff[], unsigned int dim);
void displayBuff(int error_buff[], unsigned int dim);
int checkBuff(int error_buff[], unsigned int dim);

void setAngle(int angle);



#endif /* CONTROLLER_H_ */