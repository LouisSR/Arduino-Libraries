
#include <Servo.h>
#include "Stampede.h"


#define THROTTLE_PIN 10  // attach ESC to pin 10
#define STEERING_PIN 9   // attach steering servo to pin 9

Stampede stampede(THROTTLE_PIN,STEERING_PIN);

int speed = 0;
int increment = 2;

void setup() 
{  
	stampede.begin();
	delay(1000); // wait for ESC
	// start serial port
	Serial.begin(19200);
	Serial.println("Stampede Test");
	stampede.setSpeed(0);
	delay(5000);
}

void loop() 
{
	
	speed += increment;

	if(speed > 90)
	{
		increment = -increment;
	}
	if(speed < -20)
	{
		increment = -increment;
	}

	Serial.print("Speed: ");
	Serial.println(speed);
	stampede.setSpeed(speed);

	delay(300);
}	