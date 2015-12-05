#include <Chrono.h>

#define LOOPTIME 1000

Chrono chrono("test");
Chrono loopTime("Loop Time", LOOPTIME);


void setup(void)
{
	// start serial port
	Serial.begin(19200);
	Serial.println("Chrono Test");
	loopTime.begin();
}

void loop(void)
{

	delay(10);

	chrono.start();
	delay(50);
	chrono.stop();

	chrono.display();

	delay(10);

	loopTime.wait();

}


