/*
 * Stepper.h
 *
 * Created: 12/1/2019 6:22:13 PM
 *  Author: Bogdan
 */ 


#ifndef STEPPER_H_
#define STEPPER_H_

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

//D4, D5, D6, D7 are output ports
void Stepper_Setup_Ports();

//0 for Clock-Wise, 1 for Counter Clock-Wise
void Stepper_Step(unsigned char dir, unsigned char *stepvar);

//makes n steps in the given direction
void Stepper_n_Steps(unsigned int n, unsigned char dir, unsigned char *stepvar);

#endif /* STEPPER_H_ */