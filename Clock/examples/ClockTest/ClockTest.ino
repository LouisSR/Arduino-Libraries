
#include "Clock.h"

#define LOOPTIME 1000
#define DEBUG_PIN 8


Clock loopTime;
Clock clock;


void setup(void)
{
	// start serial port
	Serial.begin(19200);
	Serial.println("Clock Test");
	loopTime.begin(LOOPTIME);
	pinMode(DEBUG_PIN,OUTPUT);
	digitalWrite(DEBUG_PIN,LOW);
	loopTime.start();
}

void loop(void)
{
	int i=0;
	delay(10);

	clock.start();
	delay(10);
	clock.stop();

	unsigned long theTime = clock.elapsedTime();
	Serial.print(" Elapsed time is: ");
	Serial.print(theTime); 
	Serial.println(" us");

	delay(100);
	digitalWrite(DEBUG_PIN,HIGH);
	loopTime.wait();
	delay(40);
	digitalWrite(DEBUG_PIN,LOW);
}