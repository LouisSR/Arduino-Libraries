#include <I2C.h>
#include <Wire.h>

uint8_t messageReceived[COM_IN_LENGTH];

I2C i2c;

void setup() 
{
	Serial.begin(19200);
	Serial.println("I2C Test ");
}

void loop() 
{
	delay(100);
	if( 1 )
	{
		i2c.getMessage(messageReceived);
		Serial.print("Message: ");
		for(int i = 0;i<COM_IN_LENGTH-3; i++)
		{
			Serial.print(messageReceived[i]);
			Serial.print(" ");
		}
		Serial.println();
	}
}