/* e:
  spimaster

  Created 2018-1
	by Mauricio Romero Jofre, Matías García Gutiérrez

	Este sketch es una prueba del automovil, controlado mediante un arduino UNO.

*/

#include <EngineAdministrator.h>
#include <Engine.h>
#include <Car.h>

// e: PINOUT AUTOMOVIL EN ARDUINO UNO

int pinStF = 22; //status input UNO 13
int pinStN = 23; //status input UNO 12
int pinStB = 24; //status input UNO 11
int pinRET = 2; //right throttle output pwm UNO 5
int pinRES = 26; //right status output digital UNO 4
int pinLET = 3; //left throttle output pwm UNO 6
int pinLES = 27; //left status output digital UNO 7
int pinBrake = 25; // digital UNO 8
int pinAcc = 0; // analog UNO 0

// e: VARIABLES SIN UTILIZAR

int tc = 0; //traction control
float w = 1; //car width
float l = 2; // car length

// e: VARIABLES velo()

float ti = 0;
float tf = millis();
float dt;
float f;

// e: Genera un objeto 'Auto' según la clase Car definida en la librería Car.h

Car Auto(pinAcc, pinBrake, pinStB, pinStN, pinStF, tc, pinRET, pinRES, pinLET, pinLES, w, l);

void setup()
{
/* e:
* Setea la comunicación serial a 9600 baudrate y el pin 2 para interrupciones
* cuando este cambia desde LOW a HIGH.
*/
	attachInterrupt(digitalPinToInterrupt(2), velo, RISING);
	Serial.begin(9600);
}

void loop()
{
/* e:
* Indefinidamente una tras otra vez, lee los sensores y los estados de auto,
* para actuar según lo obtenido como se define en la librería Car.h. Por cada vez,
* imprime en serial en una linea 
* "'Brake'	'Accelación'	'f'	'VelL' \n"
*/
	//EA.startEngines();
  Auto.ReadSensors();
  //Auto.ReadVel(f, 1);
	Auto.ReadState();
	Auto.StateMachine();
  
  Serial.print(Auto.getBrake());
  Serial.print("\t");  
  Serial.print(Auto.getAcc());
  Serial.print("\t");
  Serial.print(f);
  Serial.print("\t");
  Serial.print(Auto.getVelL());
  Serial.print("\t");
  Serial.print(Auto.getState());
  Serial.print("\n");
	//delay(1000);
}

float deg2rad(float angle){
	/* e:
	* Realiza la conversion de angle desde grados a radianes.
	*/
	return angle*3.14/180.;
}

void velo(){
	/* e:
	* Determina el tiempo entre una interrupción y otra, para luego
	* realizar el calculo f = ( (60000 milisegundos * 8)/ (tiempo entre interrupciones) ).
	*/
  tf = millis();
  dt = (tf - ti)*8;
  ti = tf;
  f = 60000/dt;
  
}
