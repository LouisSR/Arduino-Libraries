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
	_last_state = NEUTRAL;
	_state = NEUTRAL;
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

void Stampede::setSteer(int steer)
{
	steer = constrain(steer,STEER_MIN,STEER_MAX);
	steer = map(steer,STEER_MIN,STEER_MAX,STEER_RIGHT,STEER_LEFT);
	steering.write(steer);		
}

void Stampede::setSpeed(int speed)
{
	speed = constrain(speed,SPEED_MIN,SPEED_MAX);
	
	if( -5<speed && speed<5)
	{
		speed = 0;
	}

	updateState(speed);

	switch(_state)
	{
		case FORWARD:
			speed = map(speed,0,SPEED_MAX,THROTTLE_NEUTRAL,THROTTLE_MAX);
			throttle.write(speed);
			Serial.print("Speed forward: ");
			Serial.println(speed);
			break;
		case NEUTRAL:
			throttle.write(THROTTLE_NEUTRAL);
			Serial.print("Speed neutral: ");
			Serial.println(speed);
			break;
		case BRAKING:
			speed = map(speed,SPEED_MIN,0,THROTTLE_MIN,THROTTLE_NEUTRAL);
			throttle.write(speed);
			Serial.print("Speed braking: ");
			Serial.println(speed);
			break;
		case REVERSE:
			speed = map(speed,SPEED_MIN,0,THROTTLE_MIN,THROTTLE_NEUTRAL);
			throttle.write(speed);
			Serial.print("Speed reverse: ");
			Serial.println(speed);
			break;
		default:
			throttle.write(THROTTLE_NEUTRAL);
			Serial.print("Speed error: ");
			Serial.println(speed);
			break;
	}
}

void Stampede::brake(byte brake)
{
	if(_state == BRAKING || _state == FORWARD)
	{
		setSpeed(-brake);
	}
	else // _state is REVERSE or NEUTRAL)
	{
		setSpeed(20);
	}
}

void Stampede::reverse(byte reverse)
{
	if(_state == FORWARD)
	{
		brake(reverse);
	}
	else if (_state == BRAKING)
	{
		setSpeed(0); //Neutral
	}
	else //_state is REVERSE
	{
		setSpeed(-reverse);
	}
}

void Stampede::updateState(int speed)
{
	byte new_state = _state;
	
	if(speed > 0)
	{
		new_state = FORWARD;
	}
	else if (speed < 0)
	{
		if(_state == FORWARD)
		{
			new_state = BRAKING;
		}
		else if(_state == NEUTRAL)
		{
			if(_last_state == BRAKING)
			{
				new_state = REVERSE;
			}
			else
			{
				new_state = BRAKING;
			}
		}
		//else _state is REVERSE : do not change state
	}
	else //speed == 0;
	{
		new_state = NEUTRAL;
	}

	if(new_state != _state) //update states
	{
		_last_state = _state;
		_state = new_state;
	}
}