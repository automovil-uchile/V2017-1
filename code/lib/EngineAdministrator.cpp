//#include "Arduino.h"
#include "Engine.h"
#include "EngineAdministrator.h"
#include <math.h>

EngineAdministrator::EngineAdministrator(int pinRET, int pinRES, int pinLET, int pinLES, float w, float l): _rightEngine("right", pinRET, pinRES), _leftEngine("left", pinLET, pinLES)
	/*
	This class is in charge of the coordination of the two engines of the car.

	Attribues:
		_w (float): width of the car
		_l (float): length of the car
		_state (int): state of the engines. Default setting on zero (Neutral)
		_accL (float): left engine acceleration
		_accR (float): rigth engine acceleration
		_a (float): overall acceleration
		_velL (float): left engine velocity
		_velR (float): rigth engine velocity
		_eL (float): left wheel velocity error
		_eR (float): right wheel velocity error
		_kL (float): control's tuneable paramter
		_kR (float): control's tuneable parameter 
		_acc (float): user set acceleration
		_leftEngine (Engine): left engine of the car
		_rigthEngine (Engine): rigth engine of the car
	*/
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
	/*
	Uses differential velocities on the engines of the car to get smoother curves on the road.

	Args:
		angle (float): angle of the wheels.
		acc (float): overall acceleration of the car
		vel (float): overall velocity of the car
		tc (int): traccion control (?)
		vl (int): left wheel velocity
		vr (int): rigth wheel velocity

	Returns:
		Nothing
	*/	
	_acc = acc;
	if (angle>0.0){
		/*left curve*/
		_a = _l/tan(angle);
		_accR = acc;
		_accL = acc*(_a - _w/_l)/(_a + _w/_l);
		_velL = vel*(1 - _w/2.0/_a);
	}
	else if (angle<0.0){
		/*right curve*/
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
	/*
	Sets the acceleration to zero

	Args: 
		Nothing

	Returns:
		Nothing
	*/
	_acc = 0;
	_accL = 0;
	_accR = 0;
}

void EngineAdministrator::updateAcc(){
	/*
	Updates the acceleration to the engines.

	Args:
		Nothing

	Returns:
		Nonthing
	*/

	_rightEngine.setThrottle(_accR);
	_leftEngine.setThrottle(_accL);

}

void EngineAdministrator::updateState(int state){
	/*
	Updates the state to the engines.

	Args:
		Nothing

	Returns:
		Nonthing

	*/
	_rightEngine.setState(state);
	_leftEngine.setState(state);
}

float EngineAdministrator::getAccR(){
	/*
	Returns the acceleration of the rigth engine

	Args:
		Nothing

	Returns:
		_accR (float): acceleration of the rigth engine
	*/
	return _accR;
}

float EngineAdministrator::getAccL(){
	/*
	Returns the acceleration of the left engine

	Args:
		Nothing

	Returns:
		_accL (float): acceleration of the left engine
	*/
	return _accL;
}

float EngineAdministrator::getAcc(){
	/*
	Returns the overall acceleration 

	Args:
		Nothing

	Returns:
		_acc (float): overall acceleration
	*/
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