/*
 * Diploma.c
 *
 * Created: 12/1/2019 6:12:14 PM
 * Author : Bogdan
 */ 
#include "Scan.h"

void Setup(void);

int main(void)
{
	unsigned char stepvar = 0;
	unsigned char dir = 0;
	unsigned char receive = 0;

	Setup();
	_delay_ms(1000);
    while (1) 
    {
		while (receive != START_SCAN && receive != SET_PARAMS)
		{
			receive = Serial_read_char();
		}
		if (receive == SET_PARAMS){
			set_params();
		}
		if (receive == START_SCAN){
			Scan_XY(&dir, &stepvar);
		}
		
		receive = 0;
	}
}

void Setup(void)
{
	I2c_init();
	LIDAR_configuration(0);
	Serial_setup();
	Stepper_Setup_Ports();
	Servo_setup();
	MPU_Power_Down();
	setupTimer0();
	sei();
}