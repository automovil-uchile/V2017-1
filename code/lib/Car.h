#ifndef Car_h
#define Car_h
#include "SensorStatus.h"
#include "EngineAdministrator.h"
//#include "Arduino.h"

class Car
{
  public:
    Car(int pinAcc, int pinBrake, int pinStB, int pinStN, int pinStF, int tc, int pinRET, int pinRES, int pinLET, int pinLES, float w, float l, int pinclk_dir, int pindata_dir, int nbits_dir, int sincsim_dir);
    void ReadState();
    void StateMachine();
    void ReadSensors();
    void ReadVel(float vl, float vr);
    float getVelL();
    float getVelR();
    float getAcc();
    int getBrake();
    float getAng();
    int getState();



  private:
    EngineAdministrator EngAdmin;
    int _state;
    int _tc;
    float _acc;
    float _vel;
    float _velL;
    float _velR;
    int _brake;
    int _pinBrake;
    int _pinAcc;
    int _f;
    int _b;
    int _n;
    int _pinF;
    int _pinN;
    int _pinB;
    SensorStatus _Sensors;
    float _ang;
};

#endif
