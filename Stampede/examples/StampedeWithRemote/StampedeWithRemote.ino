
#include <Servo.h>
#include "Stampede.h"
#include "Remote.h"

enum Buttons
{
	THROTTLE,
	STEERING
};

byte pins[REMOTE_NB_CHANNELS];
Stampede stampede;
Remote remote;

int speed = 0;
int steer = 0;

void setup() 
{  
	pins[THROTTLE] = REMOTE_THROTTLE_PIN;
	pins[STEERING] = REMOTE_STEERING_PIN;
	remote.begin(pins, REMOTE_NB_CHANNELS);
	stampede.begin(true);
	delay(1000); // wait for ESC
	// start serial port
	Serial.begin(19200);
	Serial.println("Stampede Test");
}

void loop() 
{
	remote.checkIfConnected();

	if( remote.isConnected() )
	{
		speed = remote.read(THROTTLE);
		steer = remote.read(STEERING);
	}
	else
	{
		speed = 0;
		steer = 0;
		Serial.println("Remote is not connected.");
	}
	
	stampede.setSteer(map(steer, -500, 500, -100, 100));

	stampede.setSpeed(map(speed, -500, 500, -100, 100));

	stampede.update();

	Serial.print("Throttle: ");
	Serial.print(speed);

	Serial.print("\t Steer: ");
	Serial.println(steer);

	Serial.println();
	delay(10);
}	