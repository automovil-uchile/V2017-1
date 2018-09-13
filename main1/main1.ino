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
int pinclkdir = 5;
int pindatadir = 6;
int sincsimdir = 7;

int nbitsdir = 10;
int tc = 0; //traction control
float w = 1; //car width
float l = 2; // car length

Car Auto(pinAcc, pinBrake, pinStB, pinStN, pinStF, tc, pinRET, pinRES, pinLET, pinLES, w, l, pinclkdir, pindatadir, nbitsdir, sincsimdir);

void setup()
{

  Serial.begin(9600);
}

void loop()
{
  //EA.startEngines();
  Auto.ReadSensors();
  Auto.ReadState();
  Auto.StateMachine();

  Serial.print(Auto.getBrake());
  Serial.print("\t");  
  Serial.print(Auto.getAcc());
  Serial.print("\t");
  Serial.print(Auto.getAng());
  Serial.print("\t");
  Serial.print(Auto.getThrottleL());
  Serial.print("\t");
  Serial.print(Auto.getThrottleR());
  Serial.print("\t");
  Serial.print(Auto.getState());
  Serial.print("\n");
  //delay(1000);
}


/*
void velo(){
  tf = millis();
  dt = (tf - ti)*8;
  ti = tf;
  f = 60000/dt;
  
}
*/
