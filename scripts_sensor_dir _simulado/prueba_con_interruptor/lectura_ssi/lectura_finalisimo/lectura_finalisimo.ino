//setup

int clk = 5;
int data = 4;
int value = 0;
int val_read = 0;
int value_actual = 0;
int perder_tiempo = 0;
int n_bits = 10;      /*modificar esto dps*/ 
int flag_transmission = 7;
int count = 0;

//inicializar valores
void setup() {
  Serial.begin(9600);
  pinMode(data, INPUT);
  pinMode(flag_transmission, OUTPUT);
  pinMode(clk, OUTPUT);
  digitalWrite(clk, HIGH); //por defecto esta en high cuando no lee
  //para probarlo voy a usar una interrupcion q llame la funcion
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2),prueba, FALLING);
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
  //Serial.print("el valor leido es: ");
  //Serial.println(value);
  digitalWrite(flag_transmission, LOW);
  return value;
}

void loop() {
  // put your main code here, to run repeatedly:
}


void prueba(){
  int asd;
  asd = direction_read(10);
  Serial.println(asd); 
}
