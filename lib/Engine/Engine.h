#ifndef Engine_h
#define Engine_h

#include "Arduino.h"

class Engine
{
	public:
		Engine(char* name, int pinthrottle, int pinstate);
		void setThrottle(float throttle);
		void setState(int state);
		//start();
		//stop();
		//getVelocity();
		//getName();
		//getState();
	private:
		char* _name;
		int _pinthrottle;
		int _pinstate;
		int _state;
		int _dutycycle;
};

#endif

