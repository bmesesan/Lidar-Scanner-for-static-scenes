#include "Two_Wire.h"

//sets the SCL frequency, with the formula: F = (F_CPU)/(16 + 2 * TWBR * Prescaler_value)
//F_SCL = 6250Hz, T_SCL = 160us
//F_SCL = 400khZ / 16
void I2c_init(void)
{
	//Setting the value of the Bit rate register
	TWBR = TWBR_VAL;
	TWCR |= (1 << TWEN);
}

//Starts the I2C communication
void I2C_start_condition(void)
{
	//Sets the bits necessary in the control register
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	//Monitor TWINT to see if the operation is done
	while (!(TWCR & (1<<TWINT)));
	//test if TWSR has the correct code after START
	if ((TWSR & 0xF8) != START);
		//Serial_write_string("\nI2C START ERROR!");
}

//Stops the I2C communication
void I2C_stop_condition(void)
{
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
	_delay_ms(1);
}

//Sends the sensor address for writing purpose
void I2C_sensor_addr_write(unsigned int addr)
{
	//put the address you want to send in the data register
	TWDR = addr;
	//start operation
	TWCR = (1 << TWINT) | (1 << TWEN);
	//Monitor TWINT to see if the operation is done
	while (!(TWCR & (1<<TWINT)));
	//test if the correct code has been set in TWSR for ADDRESS WRITE ACK
	if ((TWSR & 0xF8) != SLAW_ACK);
		//Serial_write_string("\nI2C SLAW_ACK ERROR!");
}

//Sends the sensor address for reading purpose
void I2C_sensor_addr_read(unsigned int addr)
{
	//put the address you want to send in the data register
	TWDR = addr;
	//start operation
	TWCR = (1 << TWINT) | (1 << TWEN);
	//Monitor TWINT to see if the operation is done
	while (!(TWCR & (1<<TWINT)));
	//test if the correct code has been set in TWSR for ADDRESS READ ACK
	if ((TWSR & 0xF8) != SLAR_ACK);
		//Serial_write_string("\nI2C SLAR_ACK ERROR!");
}

//Sends the register address which needs to be accessed
void I2C_send_register_address(unsigned int addr)
{
	//put the address you want to send in the data register
	TWDR = addr;
	//start operation
	TWCR = (1 << TWINT) | (1 << TWEN);
	//Monitor TWINT to see if the operation is done
	while (!(TWCR & (1<<TWINT)));
	//test if the correct code has been set in TWSR for MASTER TRANSMITTER MODE ACK
	if ((TWSR & 0xF8) != MT_DATA_ACK);
		//Serial_write_string("\nI2C MT_DATA_ACK-register ERROR!");
}

//Sends one byte of data to the slave
void I2C_data_write(unsigned int data)
{
	//put the data you want to send in the data register
	TWDR = data;
	//start operation
	TWCR = (1 << TWINT) | (1 << TWEN);
	//Monitor TWINT to see if the operation is done
	while (!(TWCR & (1<<TWINT)));
	//test if the correct code has been set in TWSR for MASTER TRANSMITTER MODE ACK
	if ((TWSR & 0xF8) != MT_DATA_ACK);
		//Serial_write_string("\nI2C MT_DATA_ACK-data ERROR!");
}

//reads one byte of data from the current accessed register and returns it
unsigned int I2C_read_byte(void)
{
	//initiate the communication
	TWCR = (1 << TWINT) | (1 << TWEN);
	//Monitor TWINT to see if the operation is done
	while (!(TWCR & (1<<TWINT)));
	//test if the correct code has been set in TWSR for MASTER RECEIVER MODE
	if ((TWSR & 0xF8) != MR_DATA_NACK);
		//Serial_write_string("\nI2C MR_DATA_NACK ERROR!");
	//return the data received from the slave
	return (TWDR);
}
