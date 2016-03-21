
#include <Servo.h>
#include "Stampede.h"
#include "Remote.h"

#define THROTTLE_PIN 7
#define STEERING_PIN 8
#define ESC_PIN 10  // attach ESC to pin 10
#define STEERING_SERVO_PIN 9   // attach steering servo to pin 9
#define NB_CHANNELS 2

enum Buttons
{
	THROTTLE,
	STEERING
};

byte pins[NB_CHANNELS];
Stampede stampede(ESC_PIN,STEERING_SERVO_PIN);
Remote remote;

int speed = 0;
int steer = 0;

void setup() 
{  
	pins[THROTTLE] = THROTTLE_PIN;
	pins[STEERING] = STEERING_PIN;
	remote.begin(pins, NB_CHANNELS);
	stampede.begin();
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
	
	stampede.setSteer(steer);
	stampede.setSpeed(speed);

	Serial.print("Throttle: ");
	Serial.print(speed);

	Serial.print("\t Steer: ");
	Serial.println(steer);

	Serial.println();
	delay(500);
}	