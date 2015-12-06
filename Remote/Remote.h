/*
  Remote.h - Library for reading remote.
  Created by Louis SR, November 15, 2015.
  Released into the public domain.
*/
#ifndef Remote_h
#define Remote_h

#include "Arduino.h"

#define MAX_NB_CHANNELS 6
#define VALUE_MAX 2000
#define VALUE_MIN 1000

class Remote
{
  public:
  	Remote(void);
  	void begin(const byte *pins, byte nb_channels);
	void setOffCenter(byte channel);
	void setSwitch(byte channel);
	void setDefault(byte channel, int channelDefault);
	int read(byte channel);
	boolean isConnected(void);
	void checkIfConnected(void);

  private:
  	unsigned int measure(byte channel);

	byte _pins[MAX_NB_CHANNELS]; 
	int _channelDefault[MAX_NB_CHANNELS]; //default value if no signal is received
	boolean _centered[MAX_NB_CHANNELS];
	boolean _switch[MAX_NB_CHANNELS];
	boolean _isConnected;
};

#endif