void loop()
{
// Controles de base
if (firstStart == 0){
firstStart = 1;
Serial.println("Starting-Kalima-led");
Serial.println("Setting time");
displayTime(); // set the board time
int setdefault = setFfactoryDefault(); // set the base programe
}
h = hour();
m = minute();
if ( pastHour != h )
{
pastHour = h;
// get new channels value from ROM
Serial.println("Get variables");
channel1 = getChannelValue(h, 0);
channel2 = getChannelValue(h, 1);
channel3 = getChannelValue(h, 2);
channel4 = getChannelValue(h, 3);
Serial.println("get channel");
channel1Step = getChannelStep(h, 0);
channel2Step = getChannelStep(h, 1);
channel3Step = getChannelStep(h, 2);
channel4Step = getChannelStep(h, 3);
//Serial.println(pastHour);
//Serial.println(h);
}
Serial.println(pastHour);
Serial.println(h);
Serial.println(pastHour);
if (lastMinute != m)
{
drive1 = channel1 + (m * channel1Step);
drive2 = channel2 + (m * channel2Step);
drive3 = channel3 + (m * channel3Step);
drive4 = channel4 + (m * channel4Step);
analogWrite(drivPin1, drive1);
analogWrite(drivPin2, drive2);
analogWrite(drivPin3, drive3);
analogWrite(drivPin4, drive4);
Serial.println(drive1);
Serial.println(drive2);
Serial.println(drive3);
Serial.println(drive4);
lastMinute = m;
}
Serial.println("Main-view");
//Serial.print"Time : ");
delay(1000);
Serial.println(pastHour);
}
