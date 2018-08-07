#ifndef Engine_h
#define Engine_h

#include "Arduino.h"

class Engine
{
	public:
		Engine(char *name, int pinthrottle, int pinstatus);
		void setThrottle(float throttle);
		void setStatus(int status);
		//start();
		//stop();
		//getVelocity();
		//getName();
		//getState();
	private:
		char* _name;
		int _pinthrottle;
		int _pinstatus;
		int _status ;
		int _dutycycle;
};

#endif

