#ifndef SensorStatus_h
#define SensorStatus_h

class SensorStatus{
    public:
        SensorStatus(int pinclk_dir, int pindata_dir, int nbits_dir, int sincsim_dir)  //hay q ir agregando las fuciones

        /*int sincsim_dir es solo para el sensor simulado */
        float get_dir();

}



#endif
~         
