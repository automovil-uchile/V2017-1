int signal_out = 12;
int value = 0;
int counter=0;
int aux=0;
int flag_lectura=0; /*si es high el slave esta leyendo el dato*/
volatile int mask = 512; /*0bx1000000000 */
int save;
void setup() {
  
  Serial.begin(9600);
  pinMode(signal_out, OUTPUT);
  attachInterrupt(0, ssi, RISING ); /*Por defecto clk es high */
  /*attachInterrupt(1, lectura_master, LOW);   /*Esta linea impide q corra normalmente.
   hay que probar con el master, sin ese todo se va a la shit*/ /* si esta leyendo
  el master al slave se resetean los counter y el flag_lectura*/
}


void loop() {
  if (flag_lectura==0){
    /*Serial.print(save, BIN);
    Serial.print("\t");
    Serial.print(counter);
    Serial.print("\t");
    Serial.println(flag_lectura);
    //Serial.println("termino de un envio");*/
    save=0;
    digitalWrite(signal_out, HIGH); /* en ssipor defecto esta en high*/ 
    int pin_pote = analogRead(A0);
    value = pin_pote;
    Serial.println(pin_pote);
  }
  else{
    //Serial.println(save);
     __asm__ __volatile__ ("nop\n\t");
  }  
  
}

void ssi(){
  
  if (counter==9){
    aux = (mask & value);
    //save = save+aux;
    digitalWrite(signal_out, aux);
    counter = 0; // si se alcanza el numero de bits se restea
    flag_lectura = 0;
    mask = 512;
  }
  else{
    aux =  (mask & value);
    aux = aux>>(9-counter);
    //save = save+aux;
    digitalWrite(signal_out, aux);
     /*value = value >> 1; */ /*cuidado puede que ṕase un cero al girarlo :O...
    aunque no debiese pasar nada.*/
    mask = mask >>1;
    counter ++;
    flag_lectura = 1;
    //save = save<<1;  
  }
}

void lectura_master(){
  counter = 0;
  flag_lectura = 0;
}






