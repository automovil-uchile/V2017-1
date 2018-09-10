/* e:
  SensorStatus.h

  Created 2018-1
	by Mauricio Romero Jofre, Matías García Gutiérrez

	Este archivo .h, es donde se refiere la clase SensorStatus, sus métodos y variables.

*/

#ifndef SensorStatus_h
#define SensorStatus_h

class SensorStatus{
    public:
        SensorStatus(int pinclk_dir, int pindata_dir, int nbits_dir, int sincsim_dir);  //hay q ir agregando las fuciones

        /*int sincsim_dir es solo para el sensor simulado */
        float get_dir();

    private:
        int _pinclk_dir;
        int _pindata_dir;
        int _nbits_dir;
        int _sincsim_dir;
};



#endif
         
