/*
  Remote.h - Library for reading remote.
  Created by Louis SR, November 15, 2015.
  Released into the public domain.
*/
#ifndef Morse_h
#define Morse_h

#include "Arduino.h"

#define NB_CHANNELS 6
#define VALUE_MAX 2000
#define VALUE_MIN 1000

class Remote
{
  public:
  	Remote( byte *pins, byte nb_channels);
	void setOffCenter(byte channel);
	void setSwitch(byte channel);
	void setDefault(byte channel, int channelDefault);
	int read(byte channel);

  private:
	byte _pins[NB_CHANNELS]; 
	int _channelDefault[NB_CHANNELS]; //default value if no signal is received
	boolean _centered[NB_CHANNELS];
	boolean _switch[NB_CHANNELS];
};

#endif