//#include "Arduino.h"
#include "Engine.h"
#include "EngineAdministrator.h"
#include <math.h>

Car::Car(int st1, int st2, int st3, int tc, int pinRET, int pinRES, int pinLET, int pinLES, float w, float l): 
EngAdmin(pinRET, pinRES, pinLET, pinLES, w, l)
{
	_tc = tc; // traction control
	_state = 0; // 0 neutro, 1 backward, 2 forward
	_acc = 0; // acceleration
	_vel = 0; // body velocity
	_velL = 0; // left engine velocity
	_velR = 0; // right engine velocity
	_ang = 0; // yaw angle

}

void Car::Spi(){
	// read spi and set 
	

}

void Car::ReadState(){
	_state = 2
}


void Car::StateMachine(){
	EngAdmin.updateState(_state);	
	if (_state=2){				
		EngAdmin.differential(_ang, _acc, _vel, _tc, _velL, _velR);
	}
	else if (_state=1){
		EngAdmin.differential(_ang, _acc, _vel, _tc, _velL, _velR);

	}
	else{
		EngAdmin.set_acc_zero();

	EngAdmin.uploadAcc();
	}
}

