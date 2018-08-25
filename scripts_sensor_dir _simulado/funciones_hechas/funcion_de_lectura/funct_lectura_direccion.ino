//variables de la funcion
int clk = 5;
int data = 4;
int value = 0;
int val_read = 0;
int value_actual = 0;
int perder_tiempo = 0;
int n_bits = 10;      /*modificar esto dps*/ 
int flag_transmission = 7;   /*Este solo se requiere para datos simulados*/
int count = 0;

void setup() {
  pinMode(data, INPUT);
  pinMode(flag_transmission, OUTPUT);
  pinMode(clk, OUTPUT);
  digitalWrite(clk, HIGH); //por defecto esta en high cuando no lee
}

int direction_read(int n_bits){
  digitalWrite(flag_transmission, HIGH);
  delay(30);
  value_actual = 0;
  count = 0;
  while(count <= (2*n_bits-1)){
    if ((1&count)==0){
      /*en este caso es count es par, correponde low*/
      perder_tiempo = perder_tiempo<<1;
      digitalWrite(clk, LOW);
      delay(1);
      count++;
      val_read = digitalRead(data);
      perder_tiempo = perder_tiempo + val_read;
    }
    else{
      value_actual = value_actual <<1;
      digitalWrite(clk, HIGH);
      delay(1);
      val_read = digitalRead(data);
      value_actual = value_actual+val_read;
      count ++;
    }
  }
  value = value_actual;
  digitalWrite(flag_transmission, LOW);
  return value;
}


void loop() {
  // put your main code here, to run repeatedly:

}
