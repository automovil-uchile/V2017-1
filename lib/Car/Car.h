#ifndef Car_h
#define Car_h

#include "EngineAdministrator.h"
//#include "Arduino.h"

class Car
{
  public:
    Car(int pinSt1, int pinSt2, int pinSt3, int tc, int pinRET, int pinRES, int pinLET, int pinLES, float w, float l);
    void Spi(float acc);
    void ReadState(int state);
    void StateMachine();
    


  private:
    EngineAdministrator EngAdmin;
    int _state;
    int _tc;
    float _acc;
    float _vel;
    float _velL;
    float _velR;
    float _ang;

};

#endif