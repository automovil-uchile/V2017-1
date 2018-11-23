#include "Arduino.h"
#include "SensorStatus.h"
#include <math.h>

SensorStatus::SensorStatus(int pinclk_dir, int pindata_dir, int nbits_dir, int sincsim_dir)
{
    /*
    This class manages SPI communication between the Arduino board and yaw angle sensor.

    Attributes:
        _nbits_dir (int): 
        _pinclk_dir (int): 
        _pindata_dir (int): 
        _sincsim_dir (int): 

    */
    // setup
    pinMode(pinclk_dir, OUTPUT);
    pinMode(pindata_dir, INPUT);
    pinMode(sincsim_dir, OUTPUT);
    _nbits_dir = nbits_dir;
    _pinclk_dir = pinclk_dir;
    _pindata_dir = pindata_dir;
    _sincsim_dir = sincsim_dir;
    digitalWrite(pinclk_dir, HIGH); // default HIGH
}


float SensorStatus::get_dir(){
    /*
    Args:
        Nothing

    Returns:
        pos_degree (float):
    */
    int val_read = 0;
    int perder_tiempo = 0;
    digitalWrite(_sincsim_dir, HIGH);
    delay(30);
    int value_actual = 0;
    int count = 0;
    while(count <= (2*_nbits_dir-1)){
        if ((1&count)==0){
            perder_tiempo = perder_tiempo <<1;
            digitalWrite(_pinclk_dir, LOW);
            delay(1);
            count++;
            val_read = digitalRead(_pindata_dir);
            perder_tiempo = perder_tiempo + val_read;
        }
        else{
            value_actual = value_actual << 1;
            digitalWrite(_pinclk_dir, HIGH);
            delay(1);
            val_read = digitalRead(_pindata_dir);
            value_actual = value_actual + val_read;
            count ++;
            }
    }
    digitalWrite(_sincsim_dir, LOW);
    float pos_degree = (2*3.1416)/(pow(2,_nbits_dir))*value_actual;
    return pos_degree;
    //return value_actual;
}
