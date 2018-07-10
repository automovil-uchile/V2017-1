#include <math.h>

int a;
float angulo;
float ancho = 1;
float largo = 2;
float velocidad;
float mauro;
float mauro2;
float amax;

void setup() {
  Serial.begin(9600);
  
  // put your setup code here, to run once:

}

void loop() {
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
  diferencialInterior(angulo, velocidad);
  diferencialExterior(angulo, velocidad);
}


int diferencialInterior(float angulo, float velocidad ){
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
  amax = 45; //atan(2*largo/ancho)*180/3.1415;
  float angulo = (2*amax*ang)/1023 - amax;
  Serial.println("Angulo recibido");
  Serial.println(angulo);
  return angulo;
}

float velocidadRecibida(float vel){
  float velocidad = 100*vel/1023;
  return velocidad;
}


