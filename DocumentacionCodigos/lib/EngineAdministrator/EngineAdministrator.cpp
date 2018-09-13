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
	_velL = 0;
	_velR = 0;
	_eL = 0;
	_eR = 0;
	_kL = 1;
	_kR = 1;
	_acc = 0;
}


void EngineAdministrator::differential(float angle, float acc, float vel, int tc, float vl, float vr){
	_acc = acc;
	if (angle>0.0){
		//left curve
		_a = _l/tan(angle);
		_accR = acc;
		_accL = acc*(_a - _w/_l)/(_a + _w/_l);
		_velL = vel*(1 - _w/2.0/_a);
	}
	else if (angle<0.0){
		//right curve
		_a = _l/tan(angle);
		_accL = acc;
		_accR = acc*(_a + _w/_l)/(_a - _w/_l);
		_velR = vel*(1 + _w/2.0/_a);
	}
	else{
		_accL = acc;
		_accR = acc;
		_velL = vel;
		_velR = vel;
	}

	if (tc=1){
		_eL = _velL - vl;
		_eR = _velR - vr;
		_accL = _accL + _kL*_eL;
		_accR = _accR + _kR*_eR;
	}
}
	
void EngineAdministrator::set_acc_zero(){
	_acc = 0;
	_accL = 0;
	_accR = 0;
}

void EngineAdministrator::updateAcc(){
	_rightEngine.setThrottle(_accR);
	_leftEngine.setThrottle(_accL);

}

void EngineAdministrator::updateState(int state){
	_rightEngine.setState(state);
	_leftEngine.setState(state);
}

float EngineAdministrator::getAccR(){
	return _accR;
}

float EngineAdministrator::getAccL(){
	return _accL;
}

float EngineAdministrator::getAcc(){
	return _acc;
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