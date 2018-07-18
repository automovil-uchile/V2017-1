

#ifndef Engine_h
#define Engine_h

#include "Arduino.h"

class Engine
{
	public:
	  Engine(char *name);
	  setVelocity(int vel);
	  setPin(int pin);
	  start();
      stop();
	  getVelocity();
	  getName();
	  getState();
	  getPin();
	private:
	  char* _name;
	  int _status;
	  int _vel;
	  int _pin;
};

#endif

