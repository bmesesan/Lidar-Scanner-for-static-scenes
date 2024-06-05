/*
 * Servo_Setup.c
 *
 * Created: 11/13/2019 3:21:39 PM
 *  Author: Bogdan
 */ 

 #include "Servo_Setup.h"

 //sets up the timers, ports and interrupts for correct Servo operation
 void Servo_setup(void)
 {
	DDRB |= (1 << DDB2); //Port B.2 is an output - Timer 1
	Setup_Timer1_PC_PWM();
 }

 //Set 1000 for clock wise rotation, 1500 for stop, 2000 for Counter Clockwise rotation
 void Servo_set_rotation(unsigned int duty)
 {
	Stop_Timer1();
	Set_Timer1_duty(duty);
	Start_Timer1();
 }

 //Changes the duty cycle (in ms) of the output signal
 void Set_Timer1_duty(unsigned int duty)
 {
	 //the duty cycle is changed by setting the bottom comparison value
	 unsigned int aux = 0;

	 aux = duty & (0xFF00);
	 aux = aux >> 8;
	 OCR1BH = aux;
	 aux = duty & (0x00FF);
	 OCR1BL = aux;
 }

 //Set timer 1 with 20 ms period in Phase correct Pwm Mode
 //The duty cycle is set as a parameter
 void Setup_Timer1_PC_PWM(void)
 {
	 //Set Fast PWM Mode
	 TCCR1A |= (1 << WGM11) | (1 << WGM10) | (1 << COM1B1);
	 TCCR1B |= (1 << WGM13);
	 //Set the TOP value so that we get a signal with T = 20 ms
	 OCR1AH = 0X4E;
	 OCR1AL = 0X20;
 }

 void Start_Timer1(void)
 {
	 TCCR1B |= (1 << CS11);
 }

 void Stop_Timer1(void)
 {
	 TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10)); // Sets Prescaler to N = 0
	 TCNT1 = 0;
 }