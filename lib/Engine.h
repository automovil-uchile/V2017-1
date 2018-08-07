#ifndef Engine_h
#define Engine_h

#include "Arduino.h"

class Engine
{
	public:
		Engine(char* name, int pinthrottle, int pinstate);
		void setThrottle(float throttle);
		void setStatus(int status);
		void start();
		void stop();
		//getVelocity();
		char* getName();
		int getState();
	private:
		char* _name;
		int _pinthrottle;
		int _pinstate;
		int _state ;
		int _dutycycle;
};

#endif

