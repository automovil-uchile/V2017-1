#include "Arduino.h"
#include "Engine.h"

Engine::Engine(char* name, int pinthrottle, int pinstate)
{
	/*
	This class controls engine's state and its throttle

	Attributes:
		_name (*char): engine's name
		_pinthrottle (int): engine's output throttle pin connection
		_pinstate (int): engine's output state pin connection
		_state (int): engine's selected state
		_dutycycle (int): pwm output frequency for engine's throttle
	*/

	_name = name;
	_pinthrottle = pinthrottle;
	_pinstate = pinstate;
	_state = 0;
	_dutycycle = 0;

}

void Engine::setThrottle(float throttle){
	/*
	Sets the pwm frequency.

	Args:
		throttle (float): desired pwm frequency.

	Returns:
		Nothing
	*/
	_dutycycle = static_cast<int>(throttle*255.0);
	analogWrite(_pinthrottle, _dutycycle);
}

void Engine::setState(int state){
	/*
	Sets the desired state in engine.

	Args:
		state (int): desired state (2=forward, 1=backward, 0:idle)

	Returns:
		Nothing
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