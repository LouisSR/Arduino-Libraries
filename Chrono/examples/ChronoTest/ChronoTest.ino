#include <Chrono.h>

#define LOOPTIME 1000

Chrono chrono;
Chrono loopTime(LOOPTIME);


void setup(void)
{
	// start serial port
	Serial.begin(19200);
	Serial.println("Chrono Test");
	loopTime.start();
}

void loop(void)
{
	unsigned long theTime;

	delay(10);

	chrono.start();
	delay(50);
	chrono.stop();


	theTime = chrono.elapsedTime();

	Serial.print(" Elapsed time is: ");
	Serial.print(theTime); 
	Serial.println(" us");

	delay(10);

	loopTime.wait();

}


