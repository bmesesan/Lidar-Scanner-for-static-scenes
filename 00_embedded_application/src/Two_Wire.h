#ifndef TWO_WIRE_H_
#define TWO_WIRE_H_

#include "Serial_Communication.h"

//value of the Bit rate generator register
//set the fscl to 400kHz
#define TWBR_VAL ((F_CPU / 400000UL) - 16) / 2

//TWSR codes for different situations during the I2C transmission
#define START 0X08
#define SLAW_ACK 0x18
#define SLAW_NACK 0X20
#define MT_DATA_ACK 0x28
#define MT_DATA_NACK 0x30
#define MR_DATA_ACK 0x50
#define MR_DATA_NACK 0x58
#define SLAR_ACK 0x40
#define SLAR_NACK 0x48

//initiates the the pre-scaler and the TWBR register
//sets the SCL frequency, with the formula: F = (F_CPU)/(16 + 2 * TWBR * Prescaler_value)
void I2c_init(void);

//Starts the I2C communication
void I2C_start_condition(void);

//Stops the I2C communication
void I2C_stop_condition(void);

//Sends the sensor address for writing purpose
void I2C_sensor_addr_write(unsigned int addr);

//Sends the sensor address for reading purpose
void I2C_sensor_addr_read(unsigned int addr);

//Sends the register address which needs to be accessed
void I2C_send_register_address(unsigned int addr);

//Sends one byte of data to the slave
void I2C_data_write(unsigned int data);

//reads one byte of data from the current accessed register and returns it
unsigned int I2C_read_byte(void);

#endif /* TWO_WIRE_H_ */