#include <Remote.h>

#define CHANNEL1 7	//Digital pin
#define CHANNEL2 7	//Analog pin
#define CHANNEL3 7	//Digital pin
#define CHANNEL4 7	//Analog pin
#define CHANNEL5 7	//Digital pin
#define CHANNEL6 7	//Analog pin
#define NB_CHANNELS 6

byte channels[] = {CHANNEL1,CHANNEL2,CHANNEL3,CHANNEL4,CHANNEL5, CHANNEL6};

Remote remote(channels, NB_CHANNELS);

void setup(void)
{
	// start serial port
	Serial.begin(19200);
	Serial.println("Remote Test");
	remote.setOffCenter(3);
	remote.setSwitch(6);
	remote.setDefault(6,1);
}

void loop(void)
{
	int value;
	for(int i=1;i<=6;i++)
	{
		value = remote.read(i);
		Serial.print("Channel ");
		Serial.print(i);
		Serial.print(": ");
		Serial.println(value);
		delay(10);
	}
	Serial.println();
	delay(1000);
}

