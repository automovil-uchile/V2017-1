/* e:
  Engine.h

  Created 2018-1
	by Mauricio Romero Jofre, Matías García Gutiérrez

	Este archivo .cpp, es donde se declara la clase Engine, sus metodos y variables.

*/

#include "Arduino.h"
#include "Engine.h"

Engine::Engine(char* name, int pinthrottle, int pinstate)
{
	_name = name;
	_pinthrottle = pinthrottle;
	_pinstate = pinstate;
	_state = 0;
	_dutycycle = 0;

}

void Engine::setThrottle(float throttle){
	_dutycycle = static_cast<int>(throttle*255.0);
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
		digitalWrite(_pinstate, 1);
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