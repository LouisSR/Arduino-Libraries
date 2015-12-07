/*
	Chrono.h - Library for measuring the computational time of a function.
	Created by Louis SR, December 5, 2015.
	Released into the public domain.
*/

#ifndef Chrono_h
#define Chrono_h

#include "Arduino.h"

class Chrono
{
	public:
		Chrono(unsigned int interval_ms=0);
		void start(void);
		void stop(void);
		unsigned long elapsedTime(void);
		void wait(void);
	
	private:
		unsigned long _tic;
		unsigned long _toc;
		unsigned long _interval_us;
};

#endif