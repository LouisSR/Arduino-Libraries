 /*
  Remote.cpp - Library for reading remote.
  Created by Louis SR, November 15, 2015.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Remote.h"

Remote::Remote(void)
{
}

void Remote::begin(const byte *pins, byte nb_channels, bool debug)
{
	_debug = debug;
	if (nb_channels > MAX_NB_CHANNELS)
	{
		nb_channels = MAX_NB_CHANNELS;
	}
	for(byte channel=0;channel<nb_channels;channel++)
	{
		pinMode(pins[channel], INPUT);
		_pins[channel] = pins[channel];
		_centered[channel]=true;
		_switch[channel]=false;
		_channelDefault[channel]=0;
	}
}

void Remote::setOffCenter(byte channel)
{
	_centered[channel]=false;
}

void Remote::setSwitch(byte channel)
{
	_switch[channel] = true;
}

void Remote::setDefault(byte channel, int channelDefault)
{
	_channelDefault[channel] = channelDefault;
}

unsigned int Remote::measure(byte channel)
{
	unsigned int measurement;

	measurement = pulseIn(_pins[channel], HIGH, 6000); // 30000 for servo at 50Hz, 5500 at 300Hz
	
	if(_debug)
	{
		printUnsigned("Remote Measure: ", measurement);
	}

	return(measurement); 
}

int Remote::read(byte channel)
{
	int value;
	value = (int) measure(channel);
	if(value == 0) // no signal
	{
		value = _channelDefault[channel];
	}
	else
	{
		value = constrain(value,VALUE_MIN,VALUE_MAX);
		if(_switch[channel] == true)
		{
			if(value > 0.9*VALUE_MAX)
			{
				value = 2;
			}
			else if(value < 1.2*VALUE_MIN)
			{
				value = 0;
			}
			else 
			{
				value = 1;
			}
		}
		else
		{
			if(_centered[channel] == true)
			{
				value = value - (VALUE_MAX+VALUE_MIN)/2;
			}
			else
			{
				value = value - VALUE_MIN;
			}
		}
	}
	return value;
}

bool Remote::isConnected(void)
{
	return(_isConnected);
}

void Remote::checkIfConnected(void)
{
	if(measure(0) != 0)
	{
		_isConnected = true;
	}
	else
	{
		_isConnected = false;
	}
}