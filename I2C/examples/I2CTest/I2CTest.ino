#include <I2C.h>
#include <Wire.h>

#define SLAVE_ADDRESS 0x12

uint8_t messageReceived[COM_IN_LENGTH];
uint8_t message2send[]={0,0};

uint8_t iter = 0;

void setup() 
{
	i2cBegin(SLAVE_ADDRESS);
	Serial.begin(19200);
	Serial.println("I2C Test ");
	i2cSetMessage(message2send);
}

void loop() 
{
	boolean new_message = 0;

	new_message = i2cGetMessage(messageReceived);

	if( new_message )
	{
		//Display message received
		Serial.print("Message: ");
		for(int i = 0;i<COM_IN_LENGTH-COM_OVERHEAD; i++)
		{
			Serial.print(messageReceived[i]);
			Serial.print(" ");
		}
		Serial.println();

		//Update message to send
		message2send[0] = 76 - iter;
		message2send[1] = 105 + iter;
		i2cSetMessage(message2send);
		iter++;
	}
	delay(100);
}