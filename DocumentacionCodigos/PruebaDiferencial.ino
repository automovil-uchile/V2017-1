/* e:
  PruebaDiferencial

  Created 2018-1
	by Mauricio Romero Jofre, Matías García Gutiérrez

	Este sketch es una prueba.

	Adquiere datos desde dos sensores analógicos, uno para
	velocidad y otro para dirección. Para luego controlar dos motores de forma
	diferencial que representan	los motores de las ruedas del automovil de 
	beaucheff proyecta.

*/

#include <math.h>

int a;
float angulo;
float ancho = 1;
float largo = 2;
float velocidad;
float mauro; // e: Lectura analógica del pin 0, sensor de dirección (ángulo).
float mauro2; // e: Lectura analógica del pin 1, sensor de velocidad.
float amax;

void setup() {
	// e: Inicia y setea la comunicación serial a 9600 baudrate.
  Serial.begin(9600);
  
  // put your setup code here, to run once:

}

void loop() {
	/* e:
	* Obtiene la velocidad y dirección (ángulo), para controlar la velocidad de giro de los motores
	* de cada rueda trasera. Para lo anterior, el control se realiza de forma diferencial.
	*
	*/

  mauro = analogRead(0);
  mauro2 = analogRead(1);
  velocidad = velocidadRecibida(mauro2);
  Serial.println("Pote:");
  Serial.println(velocidad);
  angulo = anguloRecibido(mauro);
  diferencial(angulo, velocidad);
  delay(2000);
}

void diferencial(float angulo, float velocidad){
	/* e:
	* Aplica el algoritmo para obtener las velocidades de cada rueda.
	*/
  diferencialInterior(angulo, velocidad);
  diferencialExterior(angulo, velocidad);
}


int diferencialInterior(float angulo, float velocidad ){
	/* e:
	* Realiza un calculo matemático para obtener la velocidad interior, envía por serial los resultados
	* y luego envía esta velocidad de forma analógica al pin 11.
	*/

  float anguloRadianes = angulo*3.1415/180.0;
  a = largo/(tan(anguloRadianes));
  float angularVelocity = velocidad/a;
  int velocidad1 = angularVelocity*(a-ancho/2);

  Serial.println("Velocidad nueva interior:");
  Serial.println(velocidad1);
  Serial.println("radio de giro");
  Serial.println(a);

  analogWrite(11,velocidad1);
  return velocidad1;
   
}

int diferencialExterior(float angulo, float velocidad){
	/* e:
	* Realiza un calculo matemático para obtener la velocidad exterior, envía por serial los resultados
	* y luego envía esta velocidad de forma analógica al pin 10.
	*/
  float anguloRadianes = angulo*3.1415/180.0;
  a = largo/(tan(anguloRadianes));
  float angularVelocity = velocidad/a;
  int velocidad2 = angularVelocity*(a+ancho/2);

  Serial.println("Velocidad nueva exterior:");
  Serial.println(velocidad2);

  analogWrite(10,velocidad2);
  return velocidad2;
}

float anguloRecibido(float ang){
	/* e:
	* Función de conversión de la lectura analógica de ángulo del sensor de dirección.
	*/

  amax = 45; //atan(2*largo/ancho)*180/3.1415;
  float angulo = (2*amax*ang)/1023 - amax;
  Serial.println("Angulo recibido");
  Serial.println(angulo);
  return angulo;
}

float velocidadRecibida(float vel){
	/* e:
	* Función de conversión de la lectura analógica de velocidad del sensor de velocidad.
	*/
  float velocidad = 100*vel/1023;
  return velocidad;
}


