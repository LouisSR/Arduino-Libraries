
#include "Chrono.h"

#define LOOPTIME 1000


Chrono loopTime;
Chrono chrono;


void setup(void)
{
	// start serial port
	Serial.begin(19200);
	Serial.println("Chrono Test");
	loopTime.begin(LOOPTIME);
	loopTime.start();
}

void loop(void)
{
	delay(10);

	chrono.start();
	delay(50);
	chrono.stop();

	unsigned long theTime = chrono.elapsedTime();
	Serial.print(" Elapsed time is: ");
	Serial.print(theTime); 
	Serial.println(" us");

	delay(10);

	loopTime.wait();
}