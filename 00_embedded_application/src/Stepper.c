#include "Stepper.h"
#include "Serial_Communication.h"

void Stepper_Setup_Ports()
{
	DDRD |= (1 << DDD7) | (1 << DDD6) | (1 << DDD5) | (1 << DDD4);
}


void Stepper_Step(unsigned char dir, unsigned char *stepvar)
{
	unsigned char A, B ,C;
	unsigned char aux = 0;
	unsigned char i = *stepvar;

	A = ((i & 0b00000100) >> 2);
	B = ((i & 0b00000010) >> 1);
	C = (i & 0b00000001);

	aux =  (((A & B) | (A & C)) << 3) +
	((((A & (B ^ 0x01)) | ((((A ^ 0X01) & B)) & C))) << 2) +
	((((A ^ 0x01) & C) | ((A ^ 0x01) & B)) << 1) +
	(((A ^ 0x01) & (B ^ 0x01)) | ((A & B) & C)) ;


	aux = (aux << 4);
	
	PORTD &= 0b00001111;
	PORTD |= aux;

	if (dir == 1)
	{
		
		if (i == 7)
		{
			i = 0;
			*stepvar = i;
		}
		else
		{
			i++;
			*stepvar = i;
		}
	}
	else
	{
		if (i == 0)
		{
			i = 7;
			*stepvar = 7;
		}
		else
		{
			i--;
			*stepvar = i;
		}
	}
}

//makes n steps in the given direction
void Stepper_n_Steps(unsigned int n, unsigned char dir, unsigned char *stepvar)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		Stepper_Step(dir, stepvar);
		_delay_ms(2);
	}
}