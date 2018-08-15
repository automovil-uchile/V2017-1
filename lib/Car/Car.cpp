//#include "Arduino.h"
#include "Car.h"
#include "EngineAdministrator.h"

Car::Car(int pinSt1, int pinSt2, int piSt3, int tc, int pinRET, int pinRES, int pinLET, int pinLES, float w, float l): EngAdmin(pinRET, pinRES, pinLET, pinLES, w, l)
{
	_tc = tc; // traction control
	_state = 0; // 0 neutro, 1 backward, 2 forward
	_acc = 0.0; // acceleration
	_vel = 1.0; // body velocity
	_velL = 1.0; // left engine velocity
	_velR = 1.0; // right engine velocity
	_ang = 0.0; // yaw angle
	_brake = 0; // brake on/off

}

void Car::ReadAcc(float acc){
	// read spi and set 
	_acc = acc;

}

void Car::ReadBrake(int brake){
	_brake = brake;
}

void Car::ReadState(int state){
	_state = state;
}


float Car::getAcc(){
	return EngAdmin.getAcc();
}

void Car::StateMachine(){
	EngAdmin.updateState(_state);


	if (_brake==1 || _state==0){
		_acc = 0;
	}
		//set driver state 1
	
	EngAdmin.differential(_ang, _acc, _vel, _tc, _velL, _velR);
	EngAdmin.updateAcc();
}

