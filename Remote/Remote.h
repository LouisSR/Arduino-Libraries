/*
  Remote.h - Library for reading remote.
  Created by Louis SR, November 15, 2015.
  Released into the public domain.
*/
#ifndef Remote_h
#define Remote_h

#include "Arduino.h"
#include "Utils.h"

#define MAX_NB_CHANNELS 6
#define VALUE_MAX 2000
#define VALUE_MIN 1000

class Remote
{
  public:
  	Remote(void);
  	void begin(const byte *pins, byte nb_channels, bool debug);
	void setOffCenter(byte channel);
	void setSwitch(byte channel);
	void setDefault(byte channel, int channelDefault);
	int read(byte channel);
	bool isConnected(void);
	void checkIfConnected(void);

  private:
  	unsigned int measure(byte channel);

	byte _pins[MAX_NB_CHANNELS]; 
	int _channelDefault[MAX_NB_CHANNELS]; //default value if no signal is received
	bool _centered[MAX_NB_CHANNELS];
	bool _switch[MAX_NB_CHANNELS];
	bool _isConnected;
	bool _debug;
};

#endif