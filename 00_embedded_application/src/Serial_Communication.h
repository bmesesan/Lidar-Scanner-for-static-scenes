
#ifndef SERIAL_COMMUNICATION_H_
#define SERIAL_COMMUNICATION_H_


#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

//BAUD rate of the serial communication
#define BAUD 76800
#define BRC ((F_CPU/16/BAUD) - 1)

//sets up the serial port, making it ready for communication
void Serial_setup(void);

//Writes a single character on the serial line
void Serial_write_char(char c);

//Reads a single 8-bit value, incoming from the Serial port
unsigned char Serial_read_char(void);

//displays an integer number on the serial port
void Serial_write_int(int num);

//returns the mirrored number of the input
unsigned int mirr_number(unsigned int num);

//returns the number of digits in a given number
unsigned int nr_cif(unsigned int num);

//Displays a string on the serial port
void Serial_write_string(char* str);

//displays a rational number on the serial port
void Serial_write_double(double num);


#endif /* SERIAL_COMMUNICATION_H_ */