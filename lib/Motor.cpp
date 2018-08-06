#include "Arduino.h"
#include "Motor.h"

Motor::Motor(char* name, int pinthrottle, int pinstatus)
{
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

void Motor::setStatus(int status){
	/*
	2: forward
	1: backward
	0: idle
	*/
	_status = status;
	if (_status==2){
		digitalWrite(_pinstatus, 1);
	}
	else if (_status==1){
		digitalWrite(_pinstatus, 0);
	}
	else{
		analogWrite(_pinthrottle, 0);
	}
}

/*
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