#ifndef LIDAR_LITE_V3_H_
#define LIDAR_LITE_V3_H_

#include "Two_Wire.h"

//the LIDAR address for reading purposes
#define LIDAR_READ 0b11000101
//the LIDAR address for writing purposes
#define LIDAR_WRITE 0b11000100

//The register addresses of the Garmin LIDAR_LITE_V3 Sensor
#define ACQ_COMMAND 0X00

//Status register
#define STATUS_REG 0x01

//Maximum number of acquisitions during measurement
#define SIG_COUNT_VAL 0X02

//Acquisition mode control
#define ACQ_CONFIG_REG 0X04

//Velocity measurement output
#define VELOCITY 0x09

//Peak value in correlation record
#define PEAK_CORR 0X0C

//Correlation record noise floor
#define NOISE_PEAK 0X0D

//Received signal strength
#define SIGNAL_STRENGTH 0X0E

//Distance measurement high byte
#define FULL_DELAY_HIGH 0X0F

//Distance measurement low byte
#define FULL_DELAY_LOW 0X10

//Burst measurement count control
#define OUTER_LOOP_COUNT 0X11

//Reference acquisition count
#define REF_COUNT_VAL 0X12

//Previous distance measurement high byte
#define LAST_DELAY_HIGH 0x14

//Previous distance measurement low byte
#define LAST_DELAY_LOW 0x15

//Serial number high byte
#define UNIT_ID_HIGH 0x16

//Serial number low byte
#define UNIT_ID_LOW 0x17

//Write serial number high byte for I2C address unblock
#define I2C_ID_HIGH 0x18

//Write serial number low byte for I2C address unblock
#define I2C_ID_LOW 0X19

//Write new I2C address after unblock
#define I2C_SEC_ADDR 0X1A

//Peak detection threshold bypass
#define THRESHOLD_BYPASS 0X1C

//default address response control
#define I2C_CONFIG 0X1E

//state command
#define COMMAND 0X40

//delay between automatic measurements
#define MEASURE_DELAY 0X45

//second largest peak value in correlation record
#define PEAK_BCK 0X4C

//correlation record low byte
#define CORR_DATA 0X52

//correlation record high byte
#define CORR_DATA_SIGN 0X53

//correlation record memory bank select
#define ACQ_SETTINGS 0X5D

//Power state control
#define POW_CONTROL 0X65


//writes the 8-bit data to one of the registers
void LIDAR_write_data_to_register(unsigned int addr, unsigned int data);

//returns the 8-bit data from one of the registers
unsigned int LIDAR_read_data_from_register(unsigned int addr);

//returns the distance in centimeters
unsigned int LIDAR_distance_measurement(void);

//Sets up the sensing parameters, depending on the desired mode of operation
//The recommended configurations were taken from the library provided by Garmin
void LIDAR_configuration(unsigned int mode);

//wakes up the LIDAR and performs a series of measurements in order to stabilize the sensor
//write 0x00 to PWR management register
void LIDAR_Power_Up(void);

//LIDAR enters sleep mode
//write 0x04 to PWR management register
void LIDAR_Power_Down(void);

#endif /* LIDAR_LITE_V3_H_ */