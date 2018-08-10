#ifndef EngineAdministrator_h
#define EngineAdministrator_h

#include "Engine.h"
//#include "Arduino.h"

class EngineAdministrator
{
  public:
    EngineAdministrator(int pinRET, int pinRES, int pinLET, int pinLES, float w, float l);
    //void stopEngines();
    
    void differential(float angle, float acc);
    void setAcc();
    float getAccR();
    float getAccL();
    //setMarcha(int marcha);
    //getVelocity();
    //getMarcha();


  private:
    Engine _leftEngine;
    Engine _rightEngine;
    int _state;
    float _accL;
    float _accR;
    float _w;
    float _l;
    float _a;

};

#endif