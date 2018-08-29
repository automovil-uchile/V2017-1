#ifndef SensorStatus_h
#define SensorStatus_h

class SensorStatus{
    public:
        SensorStatus(int pinclk_dir, int pindata_dir, int nbits_dir, int sincsim_dir);  //hay q ir agregando las fuciones

        /*int sincsim_dir es solo para el sensor simulado */
        int get_dir();

    private:
        int _pinclk_dir;
        int _pindata_dir;
        int _nbits_dir;
        int _sincsim_dir;
};



#endif
         
