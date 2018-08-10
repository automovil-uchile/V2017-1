#include <EngineAdministrator.h>
#include <Engine.h>


EngineAdministrator EA(3, 4, 5, 7, 1., 2.);
// int pinRET, int pinRES, int pinLET, int pinLES, float w, float l
float a;
float b;
void setup()
{
	pinMode(3, OUTPUT);
	pinMode(4, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(7, OUTPUT);
	Serial.begin(9600);
}

void loop()
{
	//EA.startEngines();
	float ang = 10.;
	EA.differential(deg2rad(ang), 0.5);
	EA.updateAcc();
	a = EA.getAccR();
	b = EA.getAccL();
	Serial.print(a);
	Serial.print(b);
	delay(1000);
}

float deg2rad(float angle){
	return angle*3.14/180.;
}
