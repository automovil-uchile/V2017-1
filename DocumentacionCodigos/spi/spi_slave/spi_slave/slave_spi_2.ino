/* e:
  slave_spi_2

  Created 2018-1
	by ???? ???? ????, ???? ???? ????,

	Este sketch es una prueba de comunicación SPI.

	se comunica a través del protocolo SPI con el master cuando recibe la orden
	desde este, almacena lo recibido en un String y lo envía por serial cuando
	el caracter recibido es igual a '\r'.

*/

#include <SPI.h>
char buff [50];
volatile byte indx;
volatile boolean process;
byte c;

void setup (void) {
   Serial.begin (115200);
   pinMode(MISO, OUTPUT); // have to send on master in so it set as output
   SPCR |= _BV(SPE); // turn on SPI in slave mode
   indx = 0; // buffer empty
   process = false;
   SPI.attachInterrupt(); // turn on interrupt
}
ISR (SPI_STC_vect) // SPI interrupt routine { 
   byte c = SPDR; // read byte from SPI Data Register
   if (indx < sizeof buff) {
      buff [indx++] = c; // save data in the next index in the array buff
      if (c == '\r') //check for the end of the word
      process = true;
   }
}

void loop (void) {
   if (process) {
      process = false; //reset the process
      Serial.println (buff); //print the array on serial monitor
      indx= 0; //reset button to zero
   }
}
