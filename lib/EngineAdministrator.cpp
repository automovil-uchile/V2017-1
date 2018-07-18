#include "Arduino.h"
#include "Engine.h"
#include "EngineAdministrator.h"

EngineAdministrator::EngineAdministrator(int pinRightEngine, int pinLeftEngine)
{
	_rightEngine = Engine(pinRightEngine);
	_leftEngine = Engine(pinLeftEngine);
	_marcha = 0;
	_status = 0;
	_velocity = 0;
}

void EngineAdministrator::startEngines()
{
	_rightEngine.start();
	_leftEngine.start();
}

void EngineAdministrator::stopEngines()
{
	_rightEngine.stop();
	_leftEngine.stop();
}

/*
  Diferencial 
*/
int EngineAdministrator::setVelocity(int velocity, int angle)
{
	return 0;
}

void EngineAdministrator::setMarcha(int marcha)
{
	_marcha = marcha;
}

void EngineAdministrator::getVelocity()
{
	return _velocity;
}

void EngineAdministrator::getMarcha()
{
	return _marcha;
}
