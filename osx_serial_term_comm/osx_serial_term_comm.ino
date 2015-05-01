/*
Terminal2Arduino
Start OS X terminal.app
Find serial device name: ls /dev/tty.*
Open terminal session: screen [serial device name] 9600 
Close session: ctrl-A ctrl-\
\ = shift-alt-7 on some keyboards
*/

#define LED 13 
byte inbyte = 0;
boolean active = false;

void setup() {
  Serial.begin(9600); //open the serial port
  pinMode(LED, OUTPUT); 
  Serial.println("Type b to start and s to stop blinking of the Arduino LED");
  Serial.print(">"); //simulate prompt
}

void loop() {
  
  inbyte = Serial.read(); //Read one byte (one character) from serial port.
  if (inbyte == 'b') { 
    active = true; 
    Serial.println("b"); //echo the command
    Serial.print(">"); 
  }
  
  if (inbyte == 's') { 
    active = false; 
    Serial.println("s"); //echo the command
    Serial.print(">"); 
  }
  
  if (active) {
     digitalWrite(LED, HIGH);
     delay(500);
     digitalWrite(LED, LOW);
     delay(500);
   } else {
     digitalWrite(LED, LOW);
   }
}
