/*
 * Controller.c
 *
 * Created: 4/1/2020 3:46:01 PM
 *  Author: Bogdan
 */ 
 #include "Controller.h"

 volatile unsigned int countms = 0;

 void setupTimer0(void)
 {
	 //CTC mode
	 TCCR0A |= (1 << WGM01);
	 TIMSK0 |= (1 << OCIE0A);
	 OCR0A = 249;
 }

 void startTimer0(void)
 {
	 TCCR0B |= (0 << CS02 | 1 << CS01 | 1 << CS00);
 }

 void stopTimer0(void)
 {
	 TCCR0B &= ~(0 << CS02 | 1 << CS01 | 1 << CS00);
 }

 ISR (TIMER0_COMPA_vect)
 {
	 countms++;
 }


 int getPdelay(int error)
 {
	 return(error * KP);
 }

 int getPIDdelay(int error, int prev_error, double *errorI)
 {
	 double aux_errorI = *errorI;
	 double delayP, delayI, delayD, delayPID;

	 //Proportional Drive
	 delayP = (double)(error * KP);

	 //the Integral Drive will have a contribution only when the error is not very large
	 //The integral will control the DC error
	 //Serial_write_string("\nErrorI = ");
	 //Serial_write_double(aux_errorI);
	 if (error < IMAX_LIM && error > -IMAX_LIM && error != 0)
	 {
		 aux_errorI += error;
	 }
	 else
	 {
		 aux_errorI = 0;
	 }

	 //The integral error is limited
	 if (aux_errorI > IERROR_LIM)
	 {
		 aux_errorI = IERROR_LIM;
	 }
	 if (aux_errorI < -IERROR_LIM)
	 {
		 aux_errorI = -IERROR_LIM;
	 }
	 *errorI = aux_errorI;
	 //Integral Drive
	 delayI = (double)(KI * aux_errorI);

	 //if the error is 0, then the derivative drive will not have a contribution
	 if (error == 0)
	 {
		 delayD = 0;
	 }
	 else
	 {
		 //Derivative Drive, acting on past errors
		 delayD = (double)((error - prev_error) * KD);
	 }

	 //The final necessary drive
	 delayPID = delayP + delayI + delayD;
	 if ((int)(delayPID) > MAX_DELAY)
	 delayPID = MAX_DELAY;
	 if ((int)(delayPID) < -MAX_DELAY)
	 delayPID = -MAX_DELAY;

	 return ((int)(delayPID));
 }

 void Servo_Step_New(int delay_time)
 {
	 if (delay_time < 0)
	 {
		 Servo_set_rotation(SERVO_STEP_DUTY_1);
		 delay_time *= -1;
	 }
	 else
	 {
		 Servo_set_rotation(SERVO_STEP_DUTY_2);
	 }
	 countms = 0;
	 startTimer0();
	 while (countms < delay_time);
	 stopTimer0();
	 Servo_set_rotation(SERVO_STOP);
 }

 int getError(int sp, int pv)
 {
	 return (sp - pv);
 }

 void insertError(int error_buff[], int error, unsigned int *pos)
 {
	 unsigned int aux = *pos;

	 aux++;
	 if (aux == ERROR_DIM)
	 {
		 error_buff[0] = error;
		 aux = 0;
	 }
	 else
	 {
		 error_buff[aux] = error;
	 }

	 *pos = aux;
 }

 void initBuff(int error_buff[], unsigned int dim)
 {
	 unsigned int i;

	 for (i = 0; i < dim; i++)
	 {
		 error_buff[i] = 1;
	 }
 }

 void displayBuff(int error_buff[], unsigned int dim)
 {
	 unsigned int i;

	 Serial_write_string("\nBuff = ");
	 for (i = 0; i < dim; i++)
	 {
		 Serial_write_int(error_buff[i]);
		 Serial_write_char(' ');
	 }
 }

 int checkBuff(int error_buff[], unsigned int dim)
 {
	 unsigned int i;

	 for (i = 0; i < dim; i++)
	 {
		 if (error_buff[i] != 0)
		 return (0);
	 }
	 return (1);
 }

 void setAngle(int angle)
 {
	int error = 0;
	int prev_error = 0;
	double errorI = 0;
	int current_angle = 0;
	int delayPID = 0;
	//int error_buff[ERROR_DIM];
	//unsigned int pos = 0;

	//initBuff(error_buff, ERROR_DIM);
	do
	{
		 //Wake up the MPU
		 MPU_Power_Up();
		current_angle = MPU_filter_double_axis(NR_MEASUREMENTS);
		MPU_Power_Down();
		prev_error = error;
		error = getError(angle, current_angle);
		//insertError(error_buff, error, &pos);
		delayPID = getPIDdelay(error, prev_error, &errorI);
		Servo_Step_New(delayPID);
	} while (error != 0 || prev_error != 0);

 }