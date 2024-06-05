#include "LIDAR_LITE_V3.h"

//writes the 8-bit data to one of the registers
void LIDAR_write_data_to_register(unsigned int addr, unsigned int data)
{
	//start the I2C communication
	I2C_start_condition();
	//send the sensor address for writing purpose
	I2C_sensor_addr_write(LIDAR_WRITE);
	//send the selected register address to the slave
	I2C_send_register_address(addr);
	//send data to the selected register
	I2C_data_write(data);
	//stop the communication
	I2C_stop_condition();
}

//returns the 8-bit data from one of the registers
unsigned int LIDAR_read_data_from_register(unsigned int addr)
{
	unsigned int data;

	//start the I2C communication
	I2C_start_condition();
	//send the sensor address for writing purpose
	I2C_sensor_addr_write(LIDAR_WRITE);
	//send the selected register address to the slave
	I2C_send_register_address(addr);
	//stop the communication
	I2C_stop_condition();

	//start the I2C communication
	I2C_start_condition();
	//send the sensor address for writing purpose
	I2C_sensor_addr_read(LIDAR_READ);
	//read one byte from the slave
	data = I2C_read_byte();
	//stop the communication
	I2C_stop_condition();

	return (data);
}

//returns the distance in centimeters
unsigned int LIDAR_distance_measurement(void)
{
	unsigned int data;
	unsigned int distanceH;
	unsigned int distanceL;

	//Write the acquisition command to the ACQ_COMMAND register
	LIDAR_write_data_to_register(ACQ_COMMAND, 0x04);
	do 
	{
		//monitor the first bit of the status register, to know when the measurement is done
		data = LIDAR_read_data_from_register(STATUS_REG);
	} while ((data & 0x01));
	//extract the HIGH byte of the measurement
	distanceH = LIDAR_read_data_from_register(FULL_DELAY_HIGH);
	//extract the LOW byte of the measurement
	distanceL = LIDAR_read_data_from_register(FULL_DELAY_LOW);

	//put together the high byte and the low byte
	distanceH = distanceH << 8;
	distanceH = distanceH + distanceL;

	//return the result
	return (distanceH);
}

//Sets up the sensing parameters, depending on the desired mode of operation
//The recommended configurations were taken from the library provided by Garmin
/*	Parameters
	------------------------------------------------------------------------------
	configuration:  Default 0.
	0: Default mode, balanced performance.
	1: Short range, high speed. Uses 0x1d maximum acquisition count.
	2: Default range, higher speed short range. Turns on quick termination
	detection for faster measurements at short range (with decreased
	accuracy)
	3: Maximum range. Uses 0xff maximum acquisition count.
	4: High sensitivity detection. Overrides default valid measurement detection
	algorithm, and uses a threshold value for high sensitivity and noise.
	5: Low sensitivity detection. Overrides default valid measurement detection
	algorithm, and uses a threshold value for low sensitivity and noise.
*/
void LIDAR_configuration(unsigned int mode)
{
	unsigned int i;

	switch (mode)
	{
		 case 0: // Default mode, balanced performance
		 LIDAR_write_data_to_register(SIG_COUNT_VAL,0x80); // Default
		 LIDAR_write_data_to_register(ACQ_CONFIG_REG,0x08); // Default
		 LIDAR_write_data_to_register(THRESHOLD_BYPASS,0x00); // Default
		 LIDAR_write_data_to_register(OUTER_LOOP_COUNT, 0x01); //Default
		 break;

		 case 1: // Short range, high speed
		 LIDAR_write_data_to_register(SIG_COUNT_VAL,0x1d);
		 LIDAR_write_data_to_register(ACQ_CONFIG_REG,0x08); // Default
		 LIDAR_write_data_to_register(THRESHOLD_BYPASS,0x00); // Default
		 LIDAR_write_data_to_register(OUTER_LOOP_COUNT, 0x01); //Default
		 break;

		 case 2: // Default range, higher speed short range
		 LIDAR_write_data_to_register(SIG_COUNT_VAL,0x80); // Default
		 LIDAR_write_data_to_register(ACQ_CONFIG_REG,0x00);
		 LIDAR_write_data_to_register(THRESHOLD_BYPASS,0x00); // Default
		 LIDAR_write_data_to_register(OUTER_LOOP_COUNT, 0x01); //Default
		 break;

		 case 3: // Maximum range
		 LIDAR_write_data_to_register(SIG_COUNT_VAL,0xff);
		 LIDAR_write_data_to_register(ACQ_CONFIG_REG,0x08); // Default
		 LIDAR_write_data_to_register(THRESHOLD_BYPASS,0x00); // Default
		 LIDAR_write_data_to_register(OUTER_LOOP_COUNT, 0x01); //Default
		 break;

		 case 4: // High sensitivity detection, high erroneous measurements
		 LIDAR_write_data_to_register(SIG_COUNT_VAL,0x80); // Default
		 LIDAR_write_data_to_register(ACQ_CONFIG_REG,0x08); // Default
		 LIDAR_write_data_to_register(THRESHOLD_BYPASS,0x80);
		 LIDAR_write_data_to_register(OUTER_LOOP_COUNT, 0x01); //Default
		 break;

		 case 5: // Low sensitivity detection, low erroneous measurements
		 LIDAR_write_data_to_register(SIG_COUNT_VAL,0x80); // Default
		 LIDAR_write_data_to_register(ACQ_CONFIG_REG,0x08); // Default
		 LIDAR_write_data_to_register(THRESHOLD_BYPASS,0xb0);
		 LIDAR_write_data_to_register(OUTER_LOOP_COUNT, 0x01); //Default
		 break;

		 case 6: //Burst measurements with the nr. of measurements = 0xFE
		 LIDAR_write_data_to_register(SIG_COUNT_VAL,0xff);
		 LIDAR_write_data_to_register(ACQ_CONFIG_REG,0x28);
		 LIDAR_write_data_to_register(THRESHOLD_BYPASS,0x00); // Default
		 LIDAR_write_data_to_register(OUTER_LOOP_COUNT, 0xFE);
		 LIDAR_write_data_to_register(MEASURE_DELAY, 0X14);//100 Hz frequency
		 break;
	}
	for (i = 0; i < 50; i++)
		LIDAR_distance_measurement();
}

//wakes up the LIDAR and performs a series of measurements in order to stabilize the sensor
//write 0x00 to PWR management register
void LIDAR_Power_Up(void)
{
	unsigned int i;

	LIDAR_write_data_to_register(POW_CONTROL, 0X00);
	_delay_ms(30);
	for (i = 0; i < 50; i++)
		LIDAR_distance_measurement();
}

//LIDAR enters sleep mode
//write 0x04 to PWR management register
void LIDAR_Power_Down(void)
{
	LIDAR_write_data_to_register(POW_CONTROL, 0x04);
}