

#ifndef Motor_h
#define Motor_h

#include "Arduino.h"

class Motor
{
	public:
	  Motor(char *name);
	  setVelocity(int vel);
	  start();
      stop();
	  getVelocity();
	  getName();
	  getState();
	private:
	  char* _name;
	  int _status;
	  int _vel;
};

#endif

