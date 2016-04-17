#include "Lighting.h"

#define REVERSE 2
#define BRAKING 3

Lighting lights(4,5,6, A0);

byte status = 0;


void setup() 
{  
	
	// start serial port
	Serial.begin(19200);
	Serial.println("Lighting Test");
	lights.begin();
	Serial.println("Change state: ");
}

void loop() 
{
	if (Serial.available() )
	{
		status = Serial.read();
	}
	

	lights.update(status);
	delay(100);
}	