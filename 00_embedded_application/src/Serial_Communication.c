#include "Serial_Communication.h"

//sets up the serial port, making it ready for communication
void Serial_setup(void)
{
	//Enable Transmission and Receiver
	UCSR0B = (1 << TXEN0) | (1 << RXEN0);
	//8 bit frame, 1 stop bit, no parity
	UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);

	//sets the High byte of the USART Baud Rate register
	UBRR0H = (BRC >> 8);
	
	//sets the Low byte of the USART Baud Rate register
	UBRR0L = BRC;
	
}

//Writes a single character on the serial line
void Serial_write_char(char c)
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1 << UDRE0) ) )
	;
	/* Put data into buffer, sends the data */
	UDR0 = c;
}

//Reads a single 8-bit value, incoming from the Serial port
unsigned char Serial_read_char(void)
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) )
	;
	/* Get and return received data from buffer */
	return UDR0;
}

//displays an integer number on the serial port
void Serial_write_int(int num)
{
	unsigned int val;
	unsigned int cif;

	//in case the number is negative
	if (num < 0)
	{
		Serial_write_char('-');
		num = num * (-1);
	}

	//we send the digits in reverse order
	val = mirr_number(num);
	//in case the number ends with a 0 we need to know the number of digits it has
	cif = nr_cif(num);

	while (val > 0)
	{
		//write digit by digit
		Serial_write_char(val % 10 + 48);
		val = val / 10;
		cif--;
	}
	 if (cif > 0 || num == 0)
	 {
		 //case in which the original number ends with a '0' digit, we send out one more '0'
		 Serial_write_char('0');
		 if (cif > 0)
		 cif--;
		 while (cif > 0)
		 {
			 Serial_write_char('0');
			 cif--;
		 }
	 }
}

//returns the mirrored number of the input
unsigned int mirr_number(unsigned int num)
{
	unsigned int val = 0;
	while (num > 0)
	{
		val = val * 10 + num % 10;
		num = num / 10;
	}
	return (val);
}

//returns the number of digits in a given number
unsigned int nr_cif(unsigned int num)
{
	unsigned int sum = 0;

	while (num > 0)
	{
		sum++;
		num = num / 10;
	}

	return (sum);
}

//Displays a string on the serial port
void Serial_write_string(char* str){
	unsigned int i = 0;

	while (str[i] != 0)
	{
		Serial_write_char(str[i]);
		i++;
	}
}

//displays a rational number on the serial port
void Serial_write_double(double num)
{
	int aux;

	if (num < 0)
	{
		Serial_write_char('-');
		num = num * (-1);
	}
	aux = (int)(num);
	Serial_write_int(aux);
	num = (double)(num - aux);
	num = num * 100;
	aux = (int)(num);
	Serial_write_char('.');
	if (aux < 10)
	{
		Serial_write_char('0');
		Serial_write_int(aux);
	}
	else
	{
		Serial_write_int(aux);
	}
}