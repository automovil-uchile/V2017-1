#include "Arduino.h"
#include "Motor.h"

Motor::Motor(char* name, int pin)
{
	pinMode(pin, OUTPUT);
	_name = name;
	_pin = pin;
	_status = 0;
	_vel = 0;

}

int Motor::setVelocity(int vel){
	if (_status == 0){
		return 0;
	}
	_vel = vel;
	return 1;
}

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