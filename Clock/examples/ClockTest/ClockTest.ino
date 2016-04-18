
#include "Clock.h"

#define LOOPTIME 100
#define DEBUG_PIN 8


Clock loopTime;
Clock clock;
Clock tempo;


void setup(void)
{
	// start serial port
	Serial.begin(115200);
	Serial.println("Clock Test");
	loopTime.begin(LOOPTIME);
	pinMode(DEBUG_PIN,OUTPUT);
	digitalWrite(DEBUG_PIN,LOW);
	loopTime.start();
	tempo.begin(500);
}

void loop(void)
{
	int i=0;
	delay(10);



	if( tempo.isItTime() )
	{
		clock.start();
		delay(10);
		clock.stop();
		unsigned long theTime = clock.elapsedTime();
		Serial.print(" Elapsed time is: ");
		Serial.print(theTime); 
		Serial.println(" us");
	}
	

	delay(100);
	digitalWrite(DEBUG_PIN,HIGH);
	loopTime.wait();
	delay(40);
	digitalWrite(DEBUG_PIN,LOW);
}