#include "Arduino.h"
#include "Motor.h"

Motor::Motor(char* name, int pinthrottle, int pinstatus)
{
	pinMode(pinstatus, OUTPUT);
	_name = name;
	_pinthrottle = pinthrottle;
	_pinstatus = pinstatus;
	_status = 0;
	_dutycycle = 0;

}

/*
int Motor::setThrottle(float throttle){
	if (_status == 0){
		return 0;
	}
	_vel = vel;
	return 1;
}
*/

void Motor::setThrottle(float throttle){
	_dutycycle = (int) throttle*255;
	analogWrite(_pinthrottle, _dutycycle);
}
/*
void Motor::setPin(int pin){
	_pin = pin;
}

void Motor::start(){
	_status == 1;
}

void Motor::stop(){
	_status == 0;
}

void Motor::getVelocity(){
	return _vel;
}

void Motor::getName(){
	return _name;
}

void Motor::getState(){
	return _state;
}

void Motor::getPin(){
	return _pin;
}
*/