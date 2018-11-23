#include "Arduino.h"
#include "Car.h"
#include "EngineAdministrator.h"
#include "SensorStatus.h"

Car::Car(int pinAcc, int pinBrake, int pinStB, int pinStN, int pinStF, int tc, int pinRET, int pinRES, int pinLET, int pinLES, float w, float l, int pinclk_dir, int pindata_dir, int nbits_dir, int sincsim_dir): EngAdmin(pinRET, pinRES, pinLET, pinLES, w, l),  _Sensors(pinclk_dir, pindata_dir, nbits_dir, sincsim_dir)
{
	/*
	This class controls the overall systems of the car, sets a medium of interaction between the read of the sensors and the actuators.

	Attributes:
		_tc (int): traction control
		_state (int): actual gear (0=neutral, 2=forward, 1=backward)
		_acc (float): user acceleration
		_vel (float): car's actual velocity
		_velL (float): left wheel actual velocity
		_velR (float): right wheel actual velocity
		_ang (float): yaw angle
		_brake (int): brake boolean as int
		_pinAcc (int): acceleration signal input pin
		_pinBrake (int): brake signal input pin
		_pinF (int): forward signal input pin
		_pinN (int): neutral signal input pin
		_pinB (int): backward signal input pin
	*/
	_tc = tc; 
	_state = 0;
	_acc = 0.0; 
	_vel = 1.0; 
	_velL = 1.0; 
	_velR = 1.0; 
	_ang = 0.0; 
	_brake = 0;
	_pinAcc = pinAcc; 
	_pinBrake = pinBrake;
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
	/*
	Read the sensors of the car

	Args:
		Nothing

	Returns:
		Nothing
	*/
	_acc = analogRead(_pinAcc)/1023.0;
	_ang = _Sensors.get_dir();
	_velL = 1; // interruption
	_velR = 1; // interruption
	_vel = 1;
	_brake = digitalRead(_pinBrake); // interruption
}

void Car::ReadVel(float vl, float vr){
	/*
	Read the velocity of the wheels of the car and updates local attributes.
	
	Args:
		vl (float): left wheel velocity
		vr (float): right wheel velocity

	Returns:
		Nothing
	*/

	_velL = vl;
	_velR = vr;
}

void Car::ReadState(){
	/*
	Reads the state of the keypad and sets the next state of the car.

	Args:
		Nothing

	Returns:
		Nothing
	*/
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
	/*
	gets the overall acceleration of the car.

	Args:
		Nothing

	Returns:
		_acc (float): overall acceleration.
	*/
	return _acc; //EngAdmin.getAcc();
}

float Car::getVelL(){
	/*
	gets the left wheel velocity.

	Args:
		Nothing

	Returns:
		_velL (float): left wheel velocity.
	*/
	return _velL;
}

float Car::getVelR(){
	/*
	gets the right wheel velocity.

	Args:
		Nothing

	Returns:
		_velR (float): right wheel velocity.
	*/
	return _velR;
}

int Car::getBrake(){
	/*
	gets the brake state.

	Args:
		Nothing

	Returns:
		_brake (int): brake state.
	*/
	return _brake;
}

float Car::getAng(){
	/*
	gets the wheel's angle

	Args:
		Nothing

	Returns:
		_ang (float): yaw angle
	*/
	return _ang;
}

int Car::getState(){
	/*
	gets the state of the car

	Args:
		Nothing

	Returns:
		_state (float): state of the car
	*/
	return _state;
}

void Car::StateMachine(){
	/*
	updates user selected car state, evaluates brake state and calculates one step control action (differential)

	Args:
		Nothing

	Returns:
		Nothing
	*/
	EngAdmin.updateState(_state);
	if (_brake==1 || _state==0){
		_acc = 0;
	}
	EngAdmin.differential(_ang, _acc, _vel, _tc, _velL, _velR);
	EngAdmin.updateAcc();
}
