#include <Engine.h>
#include <EngineAdministrator.h>


EngineAdministrator EA(5, 4, 6, 7, 1., 2.);

void setup()
{
}

void loop()
{
  EA.startEngines();
  float ang = 0.;
  EA.differential(deg2rad(ang), 5);
  delay(1000);
}

float deg2rad(float angle){
  return angle*3.14/180.;
}

