
int ledRed = 5;           //RED the pin that the LED is attached to
int ledRedVal = 0;           // the pin that the LED is attached to
int ledBlue = 6;           // BLUEthe pin that the LED is attached to
int ledBlueVal = 0;           // the pin that the LED is attached to
int ledOrange = 9;           // the pin that the LED is attached to
int ledOrangeVal = 0;           // the pin that the LED is attached to
int ledGreen = 10;           // the pin that the LED is attached to
int ledGreenVal = 0;           // the pin that the LED is attached to
int fanRelay = 2;              //relais ventilo MUST BE ON

void setup() {
  // put your setup code here, to run once:
  pinMode(ledBlue, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledOrange, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(fanRelay, OUTPUT);
 
  // on ouvre le blabla
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  // set the ledOff on all leds:
  digitalWrite(fanRelay, HIGH);
  analogWrite(ledBlue, ledBlueVal);
  Serial.print(ledBlue);
  Serial.print("/t");
  Serial.print(ledBlueVal);
  analogWrite(ledRed, ledRedVal);
  Serial.print(ledRed);
  Serial.print("/t");
  Serial.print(ledRedVal);
  analogWrite(ledOrange, ledOrangeVal);
  Serial.print(ledOrange);
  Serial.print("/t");
  Serial.print(ledOrangeVal);
  analogWrite(ledGreen, ledGreenVal);
  Serial.print(ledGreen);
  Serial.print("/t");
  Serial.print(ledGreenVal);

}
