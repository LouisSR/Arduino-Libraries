#include <Schedule.h>

#define LEDPIN 13
#define PERIODE 1000

Schedule schedule(PERIODE);
boolean ledState = LOW;

void setup(void)
{
	pinMode(13, OUTPUT);  
	// start serial port
	Serial.begin(19200);
	Serial.println("Schedule Test");
	schedule.begin();
}

void loop(void)
{

	if ( schedule.isItTime() )
	{
		ledState = !ledState; //Toggle state
		schedule.call();
		digitalWrite(LEDPIN, ledState);
	}
	
	delay(50);
}


