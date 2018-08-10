//#include "Arduino.h"
#include "Engine.h"
#include "EngineAdministrator.h"
#include <math.h>

EngineAdministrator::EngineAdministrator(int pinRET, int pinRES, int pinLET, int pinLES, float w, float l): _rightEngine("right", pinRET, pinRES), _leftEngine("left", pinLET, pinLES)
    //void startEngines();
{
	_w = w;
	_l = l;
	_state = 0;
	_accL = 0;
	_accR = 0;
	_a = 0;
}


void EngineAdministrator::differential(float angle, float acc){
	if (angle>0.){
		//left curve
		_a = _l/tan(angle);
		_accR = acc;
		_accL = acc*(_a - _w/_l)/(_a + _w/_l);
	}
	else if (angle<0.){
		//right curve
		_a = _l/tan(angle);
		_accL = acc;
		_accR = acc*(_a + _w/_l)/(_a - _w/_l);
	}
	else{
		_accL = acc;
		_accR = acc;
	}
}
	

void EngineAdministrator::setAcc(){
	_rightEngine.setThrottle(_accR);
	_leftEngine.setThrottle(_accL);

}

float EngineAdministrator::getAccR(){
	return _accR;
}

float EngineAdministrator::getAccL(){
	return _accL;
}



/*
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
*/