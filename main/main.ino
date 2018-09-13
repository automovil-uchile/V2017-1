#include <EngineAdministrator.h>
#include <Engine.h>
#include <Car.h>

int pinStF = 22; //status input UNO 13
int pinStN = 23; //status input UNO 12
int pinStB = 24; //status input UNO 11
int pinRET = 2; //right throttle output pwm UNO 5
int pinRES = 27; //right status output digital UNO 4
int pinLET = 3; //left throttle output pwm UNO 6
int pinLES = 26; //left status output digital UNO 7
int pinBrake = 25; // digital UNO 8
int pinAcc = 0; // analog UNO 0
int tc = 0; //traction control
float w = 1; //car width
float l = 2; // car length
float ti = 0;
float tf = millis();
float dt;
float f;

Car Auto(pinAcc, pinBrake, pinStB, pinStN, pinStF, tc, pinRET, pinRES, pinLET, pinLES, w, l);

void setup()
{

	Serial.begin(9600);
}

void loop()
{
	//EA.startEngines();
  Auto.ReadSensors();
  Auto.ReadVel(f, 1);
	Auto.ReadState();
	Auto.StateMachine();

  Serial.print(Auto.getBrake());
  Serial.print("\t");  
  Serial.print(Auto.getAcc());
  Serial.print("\t");
  Serial.print(f);
  Serial.print("\t");
  Serial.print(Auto.getVelL());
  Serial.print("\t");
  Serial.print(Auto.getState());
  Serial.print("\n");
	//delay(1000);
}

float deg2rad(float angle){
	return angle*3.14/180.;
}

void velo(){
  tf = millis();
  dt = (tf - ti)*8;
  ti = tf;
  f = 60000/dt;
  
}
