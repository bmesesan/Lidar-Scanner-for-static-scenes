/*
 * MPU6050.c
 *
 * Created: 3/6/2020 2:59:16 PM
 *  Author: Bogdan
 */ 
 #include "MPU6050.h"

//writes the 8-bit data to one of the registers
 void MPU_write_data_to_register(unsigned int addr, unsigned int data)
 {
	//start the I2C communication
	I2C_start_condition();
	//send the sensor address for writing purpose
	I2C_sensor_addr_write(MPU_6050_WRITE);
	//send the selected register address to the slave
	I2C_send_register_address(addr);
	//send data to the selected register
	I2C_data_write(data);
	//stop the communication
	I2C_stop_condition();
 }

//returns the 8-bit data from one of the registers
 unsigned int MPU_read_data_from_register(unsigned int addr)
 {
	unsigned int data;

	//start the I2C communication
	I2C_start_condition();
	//send the sensor address for writing purpose
	I2C_sensor_addr_write(MPU_6050_WRITE);
	//send the selected register address to the slave
	I2C_send_register_address(addr);
	//stop the communication
	I2C_stop_condition();

	//start the I2C communication
	I2C_start_condition();
	//send the sensor address for writing purpose
	I2C_sensor_addr_read(MPU_6050_READ);
	//read one byte from the slave
	data = I2C_read_byte();
	//stop the communication
	I2C_stop_condition();

	return (data);
 }

 //powers up the module from SLEEP mode by writing the value 0x00 to the power management register 1
 void MPU_Power_Up(void)
 {
	MPU_write_data_to_register(PWR_MNG1, 0x00);
	_delay_ms(30);
 }

  //Sets the device to sleep by writing 0b01000000 to the power management register 1
  void MPU_Power_Down(void)
  {
	 MPU_write_data_to_register(PWR_MNG1, 0b01000000);
  }

//data acquisition from the Gyroscope or from the Accelerometer
//mode = 0 => Gyroscope
//mode = 1 => Accelerometer
double MPU_data_acq(unsigned int addr, unsigned char  mode)
 {
	int data;
	unsigned int aux;
	double output = 0;

	//read the HIGH value of the measurement
	data = MPU_read_data_from_register(addr);
	//shift the result with 8 bits
	data = data << 8;
	//add the LOW value of the measurement
	data = data + MPU_read_data_from_register(addr + 1);
	//the result is 2's Complement, so we check the sign bit
	aux = data & (1 << 15);
	//if the number is negative, convert it to decimal by complementing all the bits, adding 1, then multiply with -1
	if (aux != 0)
	{
		data = ~(data) + 1;
		data = data * (-1);
	}
	//divide the result by the correct sensitivity
	if (mode == 0)
		output = (double)(data / GYRO_SENSITIVITY);
	if (mode == 1)
		output = (double)(data / ACCEL_SENSITIVITY);

	//return the data
	return (output);
 }

 //returns the inclination angle on a single axis
 int MPU_single_axis_angle(unsigned int addr)
 {
	double accel, angle;

	//acceleration data acquisition for the required axis
	accel = MPU_data_acq(addr, 1);
	//calculate the inclination angle
	angle = asin(accel);
	//transform the angle from radians to degrees
	angle = (angle * 180.0) / PI;

	//return the result as an integer approximation
	return ((int)(angle));
 }

 //returns the inclination angle using two axis
 int MPU_double_axis_angle(unsigned int addr1, unsigned int addr2)
 {
	double accel1, accel2, angle;

	//acceleration from the first axis
	accel1 = MPU_data_acq(addr1, 1);
	//acceleration from the second axis
	accel2 = MPU_data_acq(addr2, 1);
	//calculate inclination angle based on 2 axes
	angle = atan(accel1/ accel2);
	//transform the angle from radians to degrees
	angle = (angle * 180.0) / PI;
	//if the result is in the second quadrant, the operand is negative
	//180 degrees will be added to the result
	if (accel1 >= 0 && accel2 <= 0)
		angle += 180;
	//if the result is in the third quadrant, the operand is negative
	//180 degrees will be subtracted from the result
	if (accel1 <= 0 && accel2 <= 0)
		angle -= 180;

	//return the result as an integer approximation
	return ((int)(angle));
 }


  //applies an averaging filter on n measurements of the MPU two axis angle
 int MPU_filter_double_axis(int n)
  {
	  unsigned int i;
	  int sum = 0;

	  for (i = 0; i < n; i++)
	  {
		MPU_Power_Up();
		  sum = sum + MPU_double_axis_angle(ACCEL_XOUT_H, ACCEL_YOUT_H);
	  }
	  return (sum / n);
  }

 //returns the inclination angle using all three axis
 //axis = 0 for X axis
 //axis = 1 for Y axis
 //axis = 2 for Z axis
 int MPU_triple_axis_angle(unsigned int axis)
 {
	double accel_x, accel_y, accel_z;
	double angle, aux;

	//read the acceleration data on all of the 3 axis
	accel_x = MPU_data_acq(ACCEL_XOUT_H, 1);
	accel_y = MPU_data_acq(ACCEL_YOUT_H, 1);
	accel_z = MPU_data_acq(ACCEL_ZOUT_H, 1);

	switch (axis)
	{
		//X axis inclination
		case 0:
		aux = sqrt(accel_y * accel_y + accel_z * accel_z);
		aux = accel_x / aux;
		angle = atan(aux);
		angle = (angle * 180.0) / PI;
		return ((int)(angle));
		break;

		//Y axis inclination
		case 1:
		aux = sqrt(accel_x * accel_x + accel_z * accel_z);
		aux = accel_y / aux;
		angle = atan(aux);
		angle = (angle * 180.0) / PI;
		return ((int)(angle));
		break;

		//Z axis inclination
		case 2:
		aux = sqrt(accel_x * accel_x + accel_y * accel_y);
		aux = aux / accel_z;
		angle = atan(aux);
		angle = (angle * 180.0) / PI;
		return ((int)(angle));
		break;
	}
	return (0);
 }

