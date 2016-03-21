/*
	Remote.h - Library for reading remote.
	Created by Louis SR, November 15, 2015.
	Released into the public domain.
*/
#ifndef Stampede_h
#define Stampede_h

#include <Arduino.h>
#include <Servo.h>

#define THROTTLE_NEUTRAL 1500
#define THROTTLE_MAX 2000
#define THROTTLE_MIN 1000
#define STEER_LEFT 130 //+100
#define STEER_NEUTRAL 90
#define STEER_RIGHT 50  //-100
#define SPEED_MAX 100
#define SPEED_MIN -100
#define STEER_MAX 100
#define STEER_MIN -100
#define FORWARD 1
#define NEUTRAL	0
#define BRAKING	2
#define REVERSE	3

class Stampede
{
	public:
		Stampede(byte throttlePin, byte steeringPin);
		void begin(void);
		void setSteer(int steer);
		void setSpeed(int speed);
		void brake(byte brake);
		void reverse(byte reverse);

	private:
		byte _throttlePin;
		byte _steeringPin;
		byte _last_state;
		byte _state;
		//create servo objects
		Servo throttle;
		Servo steering;

		void updateState(int speed);
};

#endif