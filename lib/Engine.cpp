#include "Arduino.h"
#include "Engine.h"

Engine::Engine(char* name, int pinThrottle, int pinMarcha)
{
	pinMode(pinThrottle, OUTPUT);
	pinMode(pinMarcha, OUTPUT);
	_name = name;
	_pinThrottle = pinThrottle;
	_pinMarcha = pinMarcha;
	_status = 0;
	_vel = 0;

}

int Engine::setVelocity(int vel){
	if (_status == 0){
		return 0;
	}
	_vel = vel;
	return 1;
}

void Engine::setPinThrottle(int pinThrottle){
	_pinThrottle = pinThrottle;
}

void Engine::setPinMarcha(int pinMarcha){
	_pinMarcha = pinMarcha;
}

void Engine::start(){
	_status == 1;
}

void Engine::stop(){
	_status == 0;
	_vel = 0;
}

void Engine::getVelocity(){
	return _vel;
}

void Engine::getName(){
	return _name;
}

void Engine::getState(){
	return _state;
}

void Engine::getPin(){
	return _pin;
}
