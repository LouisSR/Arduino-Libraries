#include <I2C.h>
#include <Wire.h>

#define SLAVE_ADDRESS 0x12

uint8_t messageReceived[COM_IN_LENGTH];

void setup() 
{
	i2cBegin(SLAVE_ADDRESS);
	Serial.begin(19200);
	Serial.println("I2C Test ");
}

void loop() 
{
	delay(100);
	if( 1 )
	{
		i2cGetMessage(messageReceived);
		Serial.print("Message: ");
		for(int i = 0;i<COM_IN_LENGTH-3; i++)
		{
			Serial.print(messageReceived[i]);
			Serial.print(" ");
		}
		Serial.println();
	}
}