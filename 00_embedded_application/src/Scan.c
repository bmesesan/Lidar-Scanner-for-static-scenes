/*
 * Scan.c
 *
 * Created: 12/11/2019 1:38:32 PM
 *  Author: Bogdan
 */ 
 #include "Scan.h"

 unsigned int stepper_resolution = 16;
 unsigned int stepper_max_steps = 256;
 unsigned int servo_angle_resolution = 1;
 int servo_max_angle = -90;
 int servo_start_position = 0;
 unsigned int lidar_config = 0;

 int params[6] = {0, 0, 0, 0, 0, 0};

 //Sets the scanning parameters
  void set_params(void)
  {
	  int i;
	  char neg = 0;
	  unsigned char receive = 0;
	  int iter = 0;

	  for (i = 0; i < 6; i++){
		params[i] = 0;
	  }

	  i = 0;
	  receive = 0;
	  Serial_write_char(CONTINUE_SEND);
	  receive = Serial_read_char();
	  while(receive != SET_PARAMS)
	  {
			iter++;
		  if (receive == ' ')
		  {
			  if (neg == 1)
			 {
				params[i] = params[i] * (-1);
			 }
			  neg = 0;
			  i++;
		  }
		  else
		  {
			  if (receive == '-'){
				  neg = 1;
			  }
			  else
			  {
				  if (receive >= 48 && receive <= 57) {
					  params[i] = params[i] * 10 + (receive - 48);
				  }
			  }
		  }
		  Serial_write_char(CONTINUE_SEND);
		  receive = Serial_read_char();
	  }

	  stepper_resolution = params[0];
	  stepper_max_steps = params[1];
	  servo_angle_resolution = params[2];
	  servo_max_angle = params[3];
	  servo_start_position = params[4];
	  lidar_config = params[5];
	  LIDAR_configuration(lidar_config);
  }




//Takes a measurement from the LIDAR and the stepper motor makes a step
 void Scan_Step_Measurement(unsigned char dir, unsigned char *stepvar, unsigned int *stepper_count, int current_servo_angle)
 {
	 unsigned int i = *stepper_count;

	 //take a measurement with the LIDAR
	 Serial_write_int(LIDAR_distance_measurement());
	 Serial_write_char(' ');
	 //LIDAR_distance_measurement();
	 //The stepper makes one step; usually the minimum delay between steps is 2 ms
	 //An additional delay is not needed because only the measurement itself takes longer than 2 ms, if you measure it with a timer
	Stepper_n_Steps(stepper_resolution, dir, stepvar);
	 //increment the stepper counter
	 i += stepper_resolution;
	 *stepper_count = i;

	 /*if (i % 256 == 0)
	 {
		setAngle(current_servo_angle);
	}*/
 }

//The scanner makes a swipe scan on the X axis
 void Scan_X_Axis(unsigned int nr_steps, unsigned char *dir, unsigned char *stepvar, int *servo_angle)
 {
	//initialize the stepper counter
	 unsigned int stepper_count = 0;
	 int aux = *servo_angle;
	 unsigned char dir_aux = *dir;

	 //the stepper makes a number of steps, taking one measurement at every step
	 while (stepper_count < nr_steps)
	{
		Scan_Step_Measurement(dir_aux, stepvar, &stepper_count, aux);
	}
	Serial_write_int(LIDAR_distance_measurement());
	Serial_write_char(' ');

	//Send new line and carriage return
	 Serial_write_char(13);
	 Serial_write_char('\n');

	 //decrement the servo counter
	 aux -= servo_angle_resolution;
	 *servo_angle = aux;
	//when an X axis scan has completed, the servo makes a step
	setAngle(aux);
	 //Set the MPU in sleep mode
	 MPU_Power_Down();

	 //change the direction of the next X axis scan
	 dir_aux ^= 0x01;
	 *dir = dir_aux;
 }

 void Scan_XY(unsigned char *dir, unsigned char *stepvar)
 {
	//initialize the servo counter
	int servo_angle = servo_start_position;
	unsigned char dir_aux = *dir;

	 setAngle(servo_start_position);

	  dir_aux ^= 0x01;
	  Stepper_n_Steps(stepper_max_steps / 2, dir_aux, stepvar);
	   _delay_ms(100);

	 //the servo makes a certain number of steps, making a full X axis scan at every step
	 while (servo_angle >= servo_max_angle)
	{
		Scan_X_Axis(stepper_max_steps, dir, stepvar, &servo_angle);
	}
	
	 dir_aux = *dir;
	 Stepper_n_Steps(stepper_max_steps / 2, dir_aux, stepvar);
	 dir_aux ^= 0x01;
	 *dir = dir_aux;

	 Serial_write_char(127);
	//when the XY scan is done, the servo stops and is set back in its initial position
	setAngle(0);
	_delay_ms(1000);
 }