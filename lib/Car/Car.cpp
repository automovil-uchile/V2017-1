//#include "Arduino.h"
#include "Car.h"
#include "EngineAdministrator.h"

Car::Car(int pinAcc, int pinBrake, int pinStB, int pinStN, int pinStF, int tc, int pinRET, int pinRES, int pinLET, int pinLES, float w, float l): EngAdmin(pinRET, pinRES, pinLET, pinLES, w, l)
{
	_tc = tc; // traction control
	_state = 0; // 0 neutro, 1 backward, 2 forward
	_acc = 0.0; // acceleration
	_vel = 1.0; // body velocity
	_velL = 1.0; // left engine velocity
	_velR = 1.0; // right engine velocity
	_ang = 0.0; // yaw angle
	_brake = 0; // brake on/off
	_pinAcc = pinAcc; // acc pin
	_pinBrake = pinBrake; //brake pin

	// initialize pins

	pinMode(pinRET, OUTPUT);
	pinMode(pinRES, OUTPUT);
	pinMode(pinLET, OUTPUT);
	pinMode(pinLES, OUTPUT);
  	pinMode(pinBrake, INPUT);
  	pinMode(pinStF, INPUT);
  	pinMode(pinStN, INPUT);
  	pinMode(pinStB, INPUT);

}

void Car::ReadSensors(){
	_acc = analogRead(_pinAcc)/1023.0;
	_ang = 20*3.14/180; // must be in rad
	_velL = 1; // interruption
	_velR = 1; // interruption
	_vel = 1;
	_brake = digitalRead(_pinBrake); // interruption
}

void Car::ReadVel(float vl, float vr){
	_velL = vl;
	_velR = vr;
}

void Car::ReadState(int state){
	_state = state; // interruption
}


float Car::getAcc(){
	return EngAdmin.getAcc();
}

float Car::getVelL(){
	return _velL;
}

float Car::getVelR(){
	return _velR;
}

int Car::getBrake(){
	return _brake;
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

