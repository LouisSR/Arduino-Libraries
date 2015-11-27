/*
Stampede.cpp - Library for controlling Stampede ESC.
Created by Louis SR, November 15, 2015.
Released into the public domain.
*/

#include "I2C.h"

I2C::I2C(void)
{
	_new_message = false;
	//Initialize message_to_send
	for(int i=0; i<COM_OUT_LENGTH-3; i++)
	{
		message_to_send[i]=0;
	}
	Wire.begin(SLAVE_ADDRESS);
	//Wire.onReceive(receiveData);
	//Wire.onRequest(sendData);
}

boolean I2C::getMessage(uint8_t* message)
{

	if(_new_message)
	{
		//Todo: verify head, length and checksum
		int command = dataReceived[0];
		int data_length = dataReceived[1];
		int checksum = dataReceived[data_length+2];

		//Collect data
		for (int i=0;i<data_length;i++)
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

void I2C::setMessage(uint8_t* message)
{
	for(int i=0; i<COM_OUT_LENGTH-3; i++)
	{
		message_to_send[i]=message[i];
	}
}

void I2C::sendData()
{
	uint8_t data_to_send[COM_OUT_LENGTH];
	data_to_send[0] = START_BYTE;
	data_to_send[1] = COM_OUT_LENGTH-3;
	data_to_send[COM_OUT_LENGTH-1] = checksum(message_to_send, COM_OUT_LENGTH-3);
	for(int i=0; i<COM_OUT_LENGTH-3; i++)
	{
		data_to_send[i+2]=message_to_send[i];
	}
	Wire.write(data_to_send, COM_OUT_LENGTH);
}

void I2C::receiveData(int byteCount)
{
	int i = 0;
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

uint8_t I2C::checksum(uint8_t* data, uint8_t length)
{
	return 255;
}