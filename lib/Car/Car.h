#ifndef Car_h
#define Car_h

#include "EngineAdministrator.h"
//#include "Arduino.h"

class Car
{
  public:
    Car(int pinAcc, int pinBrake, int pinStB, int pinStN, int pinStF, int tc, int pinRET, int pinRES, int pinLET, int pinLES, float w, float l);
    void ReadState(int state);
    void StateMachine();
    void ReadSensors();
    void ReadVel(float vl, float vr);
    float getVelL();
    float getVelR();
    float getAcc();
    int getBrake();
    float getAng();
    


  private:
    EngineAdministrator EngAdmin;
    int _state;
    int _tc;
    float _acc;
    float _vel;
    float _velL;
    float _velR;
    float _ang;
    int _brake;
    int _pinBrake;
    int _pinAcc;

};

#endif