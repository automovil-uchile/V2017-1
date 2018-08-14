# include <SPI.h>

const int slaveSelectPin = 10;
int level;

/*
SPI.beginTransaction (SPISettings (2000000, MSBFIRST, SPI_MODE0));
digitalWrite (SS, LOW);        // assert Slave Select
byte foo = SPI.transfer (42);  // do a transfer
digitalWrite (SS, HIGH);       // de-assert Slave Select
SPI.endTransaction ();         // transaction over
 */

void setup() {
  // set the slaveSelectPin as an output:
  pinMode(slaveSelectPin, OUTPUT);
  // initialize SPI:
  SPI.begin();
}


void loop() {
  level = 9;
  digitalPotWrite(level);
  delay(1000);
}


void digitalPotWrite(int value) {
  // take the SS pin low to select the chip:
  digitalWrite(slaveSelectPin, LOW);
  delay(100);
  //  send in the address and value via SPI:
  SPI.transfer(value);
  delay(100);
  // take the SS pin high to de-select the chip:
  digitalWrite(slaveSelectPin, HIGH);
}
