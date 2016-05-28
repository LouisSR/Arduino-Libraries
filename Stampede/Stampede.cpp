/*
  Stampede.cpp - Library for controlling Stampede ESC.
  Created by Louis SR, November 15, 2015.
  Released into the public domain.
*/

#include "Stampede.h"

Stampede::Stampede(void)
{
	_last_state = NEUTRAL;
	_state = NEUTRAL;
	_steer = 0;
	_speed = 0;
}

void Stampede::begin(bool debug)
{
	_debug = debug;
	lights.begin(LIGHTS_POS, LIGHTS_REV, LIGHTS_STOP, LUMINOSITY);
	pinMode(SERVO_ESC_PIN, OUTPUT); 
	pinMode(SERVO_STEERING_PIN, OUTPUT); 
	throttle.attach(SERVO_ESC_PIN, THROTTLE_MIN, THROTTLE_MAX);  
	steering.attach(SERVO_STEERING_PIN);
	throttle.writeMicroseconds(THROTTLE_NEUTRAL);   // sets mid throttle
	steering.write(STEER_NEUTRAL);   // centers steering
}

void Stampede::update(void)
{
	unsigned int speed, battery;
	steering.write(_steer);

	updateState();

	speed = map(_speed,SPEED_MIN,SPEED_MAX,THROTTLE_MIN,THROTTLE_MAX);

	if(_speed>=0)
	{
		speed = map(_speed,0,SPEED_MAX,THROTTLE_NEUTRAL,THROTTLE_MAX);
	}
	else
	{
		speed = map(_speed,SPEED_MIN,0,THROTTLE_MIN,THROTTLE_NEUTRAL);
	}

	if(_debug)
	{
		Serial.print(_speed);
		Serial.print(", ");
		Serial.println(speed);
	}

	throttle.writeMicroseconds(speed);

	battery = batteryVoltage(BATTERY, BATTERY_LED);
	if(_debug)
	{
		Serial.print("\t\t\t BatteryVoltage: ");
		Serial.println(battery);
	}
	lights.update(_state);

}

void Stampede::setSteer(int steer)
//set steer between -100(right) and 100(left)
{
	steer = constrain(steer,STEER_MIN,STEER_MAX);
	_steer = map(steer,STEER_MIN,STEER_MAX,STEER_RIGHT,STEER_LEFT);
}

void Stampede::setSpeed(int speed)
// set speed between -100(Reverse or braking) and 100 (forward)
{
	_speed = constrain(speed,SPEED_MIN,SPEED_MAX);
	
	if( -10<_speed && _speed<10)
	{
		_speed = 0;
	}
}

void Stampede::brake(byte brake)
//brake between 0 (no braking) and 100
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

void Stampede::updateState(void)
{
	byte new_state = _state;
	
	if(_speed > 0)
	{
		new_state = FORWARD;
	}
	else if (_speed < 0)
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

	if(_debug)
	{
		switch(_state)
		{
			case FORWARD:
				Serial.print("Speed forward: ");
				break;
			case NEUTRAL:
				Serial.print("Speed neutral: ");
				break;
			case BRAKING:
				Serial.print("Speed braking: ");
				break;
			case REVERSE:
				Serial.print("Speed reverse: ");
				break;
			default:
				_speed = 0;
				Serial.print("Speed error: ");
				break;
		}
	}
}

byte Stampede::getState(void)
{
	return(_state);
}