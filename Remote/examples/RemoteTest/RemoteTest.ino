#include <Remote.h>

// Define pin number of each channel
#define NB_CHANNELS 6
#define CHANNEL1 7 
#define CHANNEL2 7
#define CHANNEL3 7 
#define CHANNEL4 7 
#define CHANNEL5 7
#define CHANNEL6 7

enum Buttons
{
	joystickLeftVertical,
	joystickLeftHorizontal,
	joystickRightHorizontal,
	joystickRightVertical,
	potentiometerVba,
	switchSwc
};

byte pins[NB_CHANNELS];

Remote remote;

void setup(void)
{
	// start serial port
	Serial.begin(19200);
	Serial.println("Remote Test");

	pins[joystickRightHorizontal] = CHANNEL1;
	pins[joystickRightVertical] = CHANNEL2;
	pins[joystickLeftVertical] = CHANNEL3;
	pins[joystickLeftHorizontal] = CHANNEL4;
	pins[potentiometerVba] = CHANNEL5;
	pins[switchSwc] = CHANNEL6;
	remote.begin(pins, NB_CHANNELS);
	remote.setOffCenter(joystickLeftVertical);
	remote.setSwitch(switchSwc);
	remote.setDefault(potentiometerVba,10);
}

void loop(void)
{
	int value;

	remote.checkIfConnected();

	if( remote.isConnected() )
	{
		for(int i=0;i<NB_CHANNELS;i++)
		{
			value = remote.read(i);
			Serial.print("Channel ");
			Serial.print(i+1);
			Serial.print(": ");
			Serial.println(value);
			delay(10);
		}
		Serial.println();
	}
	else
	{
		Serial.println("Remote is not connected.");
	}
	
	delay(1000);
}

