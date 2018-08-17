int clk = 5;
int data = 4;
int value = 0;
int transmission = 8;
int val_read = 0;
int value_actual = 0;
int perder_tiempo = 0;
int n_bits = 10;      /*modificar esto dps*/ 
int flag_transmission_master = 7;
int count = 0;

/* hay q ver tener cuidado xq en el interrupt del slave
hay un if =, un and, un write_reg, shift y un add */

void setup() {
  Serial.begin(9600);
  pinMode(data, INPUT);
  pinMode(clk, OUTPUT);
  digitalWrite(clk, HIGH);  /*el clk por defecto es 1*/
  pinMode(transmission, OUTPUT);
  /*attachInterrupt(0, enviar, LOW); /*idem.. corta el programa
  probar con el master...*//* enviar info al master..VER CUANDO!! */
  pinMode(flag_transmission_master, OUTPUT);
  digitalWrite(flag_transmission_master, HIGH);
}



void loop() {
  /*lectura del sensor*/
  delay(30);
  value_actual = 0;
  count = 0;
  while (count<= (2*n_bits-1)){
    if( (1&count) == 0){
      /*en este caso es par, cno lo q corresponde un low*/
      perder_tiempo = perder_tiempo<<1;
      digitalWrite(clk, LOW);
      count ++;
      val_read = digitalRead(data);
      perder_tiempo = perder_tiempo + val_read;
    }
    else{
      value_actual = value_actual<<1;
      digitalWrite(clk, HIGH); 
      val_read = digitalRead(data);
      value_actual = value_actual+val_read;
      count ++; 
    }
  }
  value = value_actual;
  Serial.println(value);
  //Serial.print("\t");
  //Serial.println(count);
  //Serial.println(value);
}



void enviar(){
    digitalWrite(flag_transmission_master, LOW);
    

}





