/*
	I2C.h - Library for communicating through I2C.
	Created by Louis SR, November 26, 2015.
	Released into the public domain.
*/
#ifndef I2C_h
#define I2C_h

#include <Arduino.h>
#include <Wire.h>

#define SLAVE_ADDRESS 0x12
#define COM_IN_LENGTH 6 // Length of I2C recieved data
#define COM_OUT_LENGTH 5 // Length of I2C sent data
#define START_BYTE 15

class I2C
{
	public:
		I2C(void);
		boolean getMessage(uint8_t* message);
		void setMessage(uint8_t* message);

	private:
		int dataReceived[COM_IN_LENGTH];
		uint8_t message_to_send[COM_OUT_LENGTH-3];
		boolean _new_message;

		void sendData();
		void receiveData(int byteCount);
		uint8_t checksum(uint8_t* data, uint8_t length);
};

#endif