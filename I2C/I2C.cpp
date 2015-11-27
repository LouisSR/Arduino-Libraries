/*
Stampede.cpp - Library for controlling Stampede ESC.
Created by Louis SR, November 15, 2015.
Released into the public domain.
*/

#include "I2C.h"

uint8_t i2cChecksum(uint8_t* data, uint8_t length);

uint8_t message_to_send[COM_OUT_LENGTH-3];
uint8_t dataReceived[COM_IN_LENGTH];
boolean _new_message;


void i2cBegin(uint8_t slaveAdress)
{
	_new_message = false;
	//Initialize message_to_send
	for(uint8_t i=0; i<COM_OUT_LENGTH-3; i++)
	{
		message_to_send[i]=0;
	}
	Wire.begin(slaveAdress);
	Wire.onReceive(i2cReceiveData);
	Wire.onRequest(i2cSendData);
}

boolean i2cGetMessage(uint8_t* message)
{

	if(_new_message)
	{
		//Todo: verify head, length and checksum
		uint8_t command = dataReceived[0];
		uint8_t data_length = dataReceived[1];
		uint8_t checksum = dataReceived[data_length+2];

		//Collect data
		for (uint8_t i=0;i<data_length;i++)
		{
			message[i] = dataReceived[i+2];
		}
		_new_message = false;
		return true;
	}
	else
	{
		return false;
	}
}

void i2cSetMessage(uint8_t* message)
{
	for(uint8_t i=0; i<COM_OUT_LENGTH-3; i++)
	{
		message_to_send[i]=message[i];
	}
}

void i2cSendData()
{
	uint8_t data_to_send[COM_OUT_LENGTH];
	data_to_send[0] = START_BYTE;
	data_to_send[1] = COM_OUT_LENGTH-3;
	data_to_send[COM_OUT_LENGTH-1] = i2cChecksum(message_to_send, COM_OUT_LENGTH-3);
	for(uint8_t i=0; i<COM_OUT_LENGTH-3; i++)
	{
		data_to_send[i+2]=message_to_send[i];
	}
	Wire.write(data_to_send, COM_OUT_LENGTH);
}

void i2cReceiveData(int byteCount)
{
	uint8_t i = 0;
	if (byteCount>1)
	{
		while(Wire.available()) 
		{
			dataReceived[i++] = Wire.read();
		}
		_new_message = true;  
	}
	else
	{
		Wire.read();
	}
}

uint8_t i2cChecksum(uint8_t* data, uint8_t length)
{
	return 255;
}


