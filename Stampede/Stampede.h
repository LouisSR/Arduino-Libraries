/*
	Remote.h - Library for reading remote.
	Created by Louis SR, November 15, 2015.
	Released into the public domain.
*/
#ifndef Stampede_h
#define Stampede_h

#include <Arduino.h>
#include <Servo.h>

#define THROTTLE_NEUTRAL 90
#define THROTTLE_MAX 180
#define THROTTLE_MIN 0
#define STEER_LEFT 130 //+100
#define STEER_NEUTRAL 90
#define STEER_RIGHT 50  //-100
#define SPEED_MAX 100
#define SPEED_MIN -100
#define STEER_MAX 100
#define STEER_MIN -100

class Stampede
{
	public:
		Stampede(byte throttlePin, byte steeringPin);
		void begin(void);
		void setSpeed(int speed);
		void setSteer(int steer);

	private:
		byte _throttlePin;
		byte _steeringPin;
		int _speed;
		//create servo objects
		Servo throttle;
		Servo steering;
};

#endif