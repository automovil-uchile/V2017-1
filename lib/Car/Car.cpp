//#include "Arduino.h"
#include "Car.h"
#include "EngineAdministrator.h"
#include "SensorStatus.h"

Car::Car(int pinAcc, int pinBrake, int pinStB, int pinStN, int pinStF, int tc, int pinRET, int pinRES, int pinLET, int pinLES, float w, float l): EngAdmin(pinRET, pinRES, pinLET, pinLES, w, l)// :SensorStatus(int pinclk_dir, int pindata_dir, int nbits_dir, int sincsim_dir)
// int pinclk_dir, int pindata_dir, int nbits_dir, int sincsim_dir
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
	_pinF = pinStF;
	_pinN = pinStN;
	_pinB = pinStB;


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
	_acc = analogRead(_pinAcc)/1023.0; // llega hasta 2.8V
	_ang = 0; //analogRead(1)*3.14/1023.0; //Sensor.Status();
	_velL = 1; // interruption
	_velR = 1; // interruption
	_vel = 1;
	_brake = digitalRead(_pinBrake); // interruption
}

void Car::ReadVel(float vl, float vr){
	_velL = vl;
	_velR = vr;
}

void Car::ReadState(){
	_f = digitalRead(_pinF);
	_n = digitalRead(_pinN);
	_b = digitalRead(_pinB);
	if (_f==1){
		_state = 2;
	}
	if (_n==1){
		_state = 0;
	}
	if (_b==1){
		_state = 1;
	}
}


float Car::getAcc(){
	return _acc; //EngAdmin.getAcc();
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

float Car::getAng(){
	return _ang;
}

int Car::getState(){
	return _state;
}

void Car::StateMachine(){
	EngAdmin.updateState(_state);
	if (_brake==1 || _state==0){
		EngAdmin.differential(_ang, 0, _vel, _tc, _velL, _velR);
	}
	else{
		EngAdmin.differential(_ang, _acc, _vel, _tc, _velL, _velR);
		//set driver state 1
	}	
	
	EngAdmin.updateAcc();
}

