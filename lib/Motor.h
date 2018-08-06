#ifndef Motor_h
#define Motor_h

#include "Arduino.h"

class Motor
{
	public:
		Motor(char *name, int pinthrottle, int pinstatus);
		void setThrottle(float throttle);
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

