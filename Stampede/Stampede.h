/*
	Remote.h - Library for reading remote.
	Created by Louis SR, November 15, 2015.
	Released into the public domain.
*/
#ifndef Stampede_h
#define Stampede_h

#include <Arduino.h>
#include <Servo.h>
#include "Lighting.h"
#include "Utils.h"

//Car 
#define BATTERY	A0 //Measure battery voltage on this analog pin
#define BATTERY_LED 13
#define LUMINOSITY	A1 //Measure luminosity on this analog pin
#define SERVO_ESC_PIN 10  // attach ESC to pin 10
#define SERVO_STEERING_PIN 9   // attach steering servo to pin 9
#define LIGHTS_POS A2
#define LIGHTS_REV A3
#define LIGHTS_STOP A4

//Remote 
#define REMOTE_NB_CHANNELS 3 // Number of channels of the remote used
#define REMOTE_THROTTLE_PIN 7
#define REMOTE_STEERING_PIN 8
#define	REMOTE_SWITCH_PIN 4

#define THROTTLE_NEUTRAL 1500
#define THROTTLE_MAX 1850 //max 1850 for QuicRun 1060
#define THROTTLE_MIN 1050 //min 1050 for QuicRun 1060
#define STEER_LEFT 125 //+100
#define STEER_NEUTRAL 90
#define STEER_RIGHT 60  //-100
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
		Stampede(void);
		void begin(bool debug);
		void update(void);
		void setSteer(int steer);
		void setSpeed(int speed);
		void brake(byte brake);
		void reverse(byte reverse);
		byte getState(void);

	private:
		byte _last_state;
		byte _state;
		bool _debug;
		int _speed;
		int _steer;
		Lighting lights;
		//create servo objects
		Servo throttle;
		Servo steering;

		void updateState(void);
};

#endif