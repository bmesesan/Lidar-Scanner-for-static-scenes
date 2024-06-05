/*
 * MPU6050.h
 *
 * Created: 3/6/2020 3:02:48 PM
 *  Author: Bogdan
 */ 


#ifndef MPU6050_H_
#define MPU6050_H_
#include "Two_Wire.h"
#include <math.h>

//Pi constant value
#define PI 3.14

//Gyroscope and Accelerometer sensitivity
#define GYRO_SENSITIVITY 131.0
#define ACCEL_SENSITIVITY 2048.0

//Sensor I2C addresses
#define MPU_6050_READ 0b11010001
#define MPU_6050_WRITE 0b11010000

//Gyroscope configuration register
#define GYRO_CONFIG 0x1B

//Accelerometer configuration register
#define ACCEL_CONFIG 0x1C

//Accelerometer data registers
#define ACCEL_XOUT_H 0x3B
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E
#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40

//Gyroscope data registers
#define GYRO_XOUT_H 0x43
#define GYRO_XOUT_L 0x44
#define GYRO_YOUT_H 0x45
#define GYRO_YOUT_L 0x46
#define GYRO_ZOUT_H 0x47
#define GYRO_ZOUT_L 0x48

//Power management register
#define PWR_MNG1 0x6B

//writes the 8-bit data to one of the registers
void MPU_write_data_to_register(unsigned int addr, unsigned int data);

//returns the 8-bit data from one of the registers
unsigned int MPU_read_data_from_register(unsigned int addr);

 //powers up the module from SLEEP mode by writing the value 0x00 to the power management register 1
void MPU_Power_Up(void);

 //Sets the device to sleep by writing 0x01 to the power management register 1
 void MPU_Power_Down(void);

//data acquisition from the Gyroscope or from the Accelerometer  
//mode = 0 => Gyroscope
//mode = 1 => Accelerometer
double MPU_data_acq(unsigned int addr, unsigned char  mode);

//returns the inclination angle on a single axis 
int MPU_single_axis_angle(unsigned int addr);

//returns the inclination angle using two axis
int MPU_double_axis_angle(unsigned int addr1, unsigned int addr2);

 //applies an averaging filter on n measurements of the MPU two axis angle
 int MPU_filter_double_axis(int n);

//returns the inclination angle using all three axis
//axis = 0 for X axis
//axis = 1 for Y axis
//axis = 2 for Z axis
int MPU_triple_axis_angle(unsigned int axis);



#endif /* MPU6050_H_ */