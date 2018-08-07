#include "Arduino.h"
#include "Engine.h"

Engine::Engine(char* name, int pinthrottle, int pinstate){
	_name = name;
	_pinthrottle = pinthrottle;
	_pinstate = pinstate;
	_state = 0;
	_dutycycle = 0;

}

void Engine::setThrottle(float throttle){
	_dutycycle = (int) throttle*255.;
	analogWrite(_pinthrottle, _dutycycle);
}

void Engine::setState(int state){
	/*
	2: forward
	1: backward
	0: idle
	*/
	_state = state;
	if (_state==2){
		digitalWrite(_pinstate, 1);
	}
	else if (_state==1){
		digitalWrite(_pinstate, 0);
	}
	else{
		analogWrite(_pinthrottle, 0);
	}
}


void Engine::start(){
	//It should connect a power relay, but now it changes the state to idle and zero throttle.
	_state == 0;
	digitalWrite(_pinstate, 1);
	analogWrite(_pinthrottle, 0);

}

void Engine::stop(){
	//It should disconnect a power relay, but now it changes the state to idle and zero throttle.
	_state == 0;
	digitalWrite(_pinstate, 1);
	analogWrite(_pinthrottle, 0);
}
/*
void Motor::getVelocity(){
	return _vel;
}
*/
char* Engine::getName(){
	return _name;
}

int Engine::getState(){
	return _state;
}
/*
void Motor::getPin(){
	return _pin;
}
*/