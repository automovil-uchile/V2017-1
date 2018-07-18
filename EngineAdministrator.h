
#ifndef EngineAdministrator.h
#define EngineAdministrator.h

#include "Engine.h"
#include "Arduino.h"

class EngineAdministrator
{
    public:
      EngineAdministrator(int pinRightEngine, int pinLeftEngine);
      startEngines();
      stopEngines();
      setVelocity(int velocity, int angle);
      setMarcha(int marcha);
      getVelocity();
      getMarcha();

    private:
    	Engine _leftEngine;
    	Engine _rightEngine;
    	int _marcha;
    	int _engineState;
    	float velocity;
};

#endif