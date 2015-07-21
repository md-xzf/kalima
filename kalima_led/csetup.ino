void setup()
{
pinMode(drivPin1, OUTPUT);
pinMode(drivPin2, OUTPUT);
pinMode(drivPin3, OUTPUT);
pinMode(drivPin4, OUTPUT);
pinMode(10, OUTPUT);



// initialize serial and wait for port to open:
Wire.begin();
Serial.begin(9600);
 Serial.print("Initializing SD card...");
// set the initial time here:
// DS3231 seconds, minutes, hours, day, date, month, year
// setDS3231time(30,42,21,4,26,11,14);
}
