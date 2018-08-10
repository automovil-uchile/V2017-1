#ifndef Car_h
#define Car_h

#include "EngineAdministrator.h"
//#include "Arduino.h"

class Car
{
  public:
    Car();
    void spi();
    void read();
    int tc;


  private:
    EngineAdministrator EngAdmin;
    int _state;
    int _tc;

};

#endif