/* e:
  serial

  Created 2018-1
	by ???? ???? ????, ???? ???? ????,

	Este sketch es una prueba.

	Cuando recibe algún dato por serial, dquiere dos datos consecutivos
	desde un pin analógico, para luego enviarlos por serial en el formato
	" 'val0' , 'val1'"

*/

String inByte;
int myTimeout = 90;  // milliseconds for Serial.readString
int val0 = 0;
int val1 = 0;
String Val0;
String Val1;
String string;


void setup() {
Serial.begin(115200); // set the baud rate
Serial.setTimeout(myTimeout);
Serial.println('10');
  }
void loop() {

if(Serial.available()){ // only send data back if data has been sent
inByte = Serial.readString(); // read the incoming data
val0 = analogRead(0);
val1 = analogRead(0);
Val0 = String(val0);
Val1 = String(val1);
string = Val0 + ',' + Val1;
Serial.println(string); // send the data back in a new line so that it is not all one long line
}
//delay(1); // delay for 1/10 of a second
}
