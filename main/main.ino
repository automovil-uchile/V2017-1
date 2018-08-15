#include <EngineAdministrator.h>
#include <Engine.h>
#include <Car.h>

Car Auto(11, 12, 13, 0, 3, 4, 5, 6, 1, 2);
// int pinSt1, int pinSt2, int piSt3, int tc, int pinRET, int pinRES, int pinLET, int pinLES, float w, float l
float a;
float b;
int c;
void setup()
{
	pinMode(3, OUTPUT);
	pinMode(4, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
  pinMode(8, INPUT);
	Serial.begin(9600);
}

void loop()
{
	//EA.startEngines();
  a = analogRead(0);
  b = a/1023;
  c = digitalRead(8);
	Auto.ReadState(2);
  Auto.ReadAcc(b);
  Auto.ReadBrake(c);
	Auto.StateMachine();
  
  Serial.print(a);
  Serial.print("\t");
  Serial.print(b);
  Serial.print("\t");
  Serial.print(c);
  Serial.print("\t");
  Serial.print(Auto.getAcc());
  
  Serial.print("\n");
	//delay(1000);
}

float deg2rad(float angle){
	return angle*3.14/180.;
}
