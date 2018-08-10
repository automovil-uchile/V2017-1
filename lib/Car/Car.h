#ifndef Car_h
#define Car_h

#include "EngineAdministrator.h"
//#include "Arduino.h"

class Car
{
  public:
    Car(int st1, int st2, int st3, int tc, int pinRET, int pinRES, int pinLET, int pinLES, float w, float l);
    void Spi();
    void ReadState();
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