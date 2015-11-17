/*
  Stampede.cpp - Library for controlling Stampede ESC.
  Created by Louis SR, November 15, 2015.
  Released into the public domain.
*/

#include "Stampede.h"

Stampede::Stampede(byte throttlePin, byte steeringPin)
{
	_throttlePin = throttlePin;
	_steeringPin = steeringPin;
	_speed = 0;
}

void Stampede::begin(void)
{
	pinMode(_throttlePin, OUTPUT); 
	pinMode(_steeringPin, OUTPUT); 
	throttle.attach(_throttlePin);  
	steering.attach(_steeringPin);
	throttle.write(THROTTLE_NEUTRAL);   // sets mid throttle
	steering.write(STEER_NEUTRAL);   // centers steering
}

void Stampede::setSpeed(int speed)
{
	speed = constrain(speed,SPEED_MIN,SPEED_MAX);
	if(speed>=0)
	{
		speed = map(speed,0,SPEED_MAX,THROTTLE_NEUTRAL,THROTTLE_MAX);
		throttle.write(speed);
	}
	else if(_speed<0)
	{
		speed = map(speed,-SPEED_MIN,0,THROTTLE_MIN,THROTTLE_NEUTRAL);
		throttle.write(speed); 
	}
	else
	{
		speed = map(speed,SPEED_MIN,0,THROTTLE_MIN,THROTTLE_NEUTRAL);
		throttle.write(speed); 
		delay(100);
		throttle.write(THROTTLE_NEUTRAL);
		delay(100);
		throttle.write(speed); 
	}
	_speed = speed;
}

void Stampede::setSteer(int steer)
{
	steer = constrain(steer,STEER_MIN,STEER_MAX);
	steer = map(steer,STEER_MIN,STEER_MAX,STEER_RIGHT,STEER_LEFT);
	steering.write(steer);		
}