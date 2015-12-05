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
		Chrono(char* name, unsigned int interval=0);
		void begin(void);
		void start(void);
		void stop(void);
		unsigned long elapsedTime(void);
		void wait(void);
		void display(void);
	
	private:
		unsigned long _tic;
		unsigned long _toc;
		char _name[11];
		unsigned long _interval;
};

#endif