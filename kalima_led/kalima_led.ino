#include <SoftwareSerial.h>
#include <EEPROM.h>
#include <Time.h>
#include "Wire.h"
#define DS3231_I2C_ADDRESS 0x68
// Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val)
{
return( (val/10*16) + (val%10) );
}
// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)
{
return( (val/16*10) + (val%16) );
}
/*
* Kalima-led
*
* Read value from serial and set rom acordigly
* Read rom according to time
*/

int time1=0;
int time2=0;
int programSelect=0;
double channel1=0;
double channel2=0;
double channel3=0;
double channel4=0;
double drive1=0;
double drive2=0;
double drive3=0;
double drive4=0;
int firstStart=0;
int duration=0;
int h=0;
int pastHour = 23;
int m=0;
int lastMinute=59;
int address = 0;
int value;
int state=0;
int pastTime=0;
double channel1Step=0;
double channel2Step=0;
double channel3Step=0;
double channel4Step=0;
double result;
double delta;
int ch=0;
int drivPin1 = 10;
int drivPin2 = 9;
int drivPin3 = 6;
int drivPin4 = 5;
int addr;
int i;
int pos;
int prevCh;
int nextCh;
int ch1[24] = {
255, 0, 0, 0, 0, 0, 0, 20, 60, 120, 255, 255, 200, 180, 160, 120, 80, 60, 20, 0, 0, 0, 0, 0};
int ch2[24] = {
255, 0, 0, 0, 0, 0, 0, 20, 60, 120, 255, 255, 200, 180, 160, 120, 80, 60, 20, 0, 0, 0, 0, 0};
int ch3[24] = {
255, 0, 0, 0, 0, 0, 0, 20, 60, 120, 255, 255, 200, 180, 160, 120, 80, 60, 20, 0, 0, 0, 0, 0};
int ch4[24] = {
255, 0, 0, 0, 0, 0, 0, 20, 60, 120, 255, 255, 200, 180, 160, 120, 80, 60, 20, 0, 0, 0, 0, 0};
void setup()
{
pinMode(drivPin1, OUTPUT);
pinMode(drivPin2, OUTPUT);
pinMode(drivPin3, OUTPUT);
pinMode(drivPin4, OUTPUT);
// initialize serial and wait for port to open:
Wire.begin();
Serial.begin(9600);
// set the initial time here:
// DS3231 seconds, minutes, hours, day, date, month, year
// setDS3231time(30,42,21,4,26,11,14);
}
// Fonction thinyRTC

void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte
dayOfMonth, byte month, byte year)
{
// sets time and date data to DS3231
Wire.beginTransmission(DS3231_I2C_ADDRESS);
Wire.write(0); // set next input to start at the seconds register
Wire.write(decToBcd(second)); // set seconds
Wire.write(decToBcd(minute)); // set minutes
Wire.write(decToBcd(hour)); // set hours
Wire.write(decToBcd(dayOfWeek)); // set day of week (1=Sunday, 7=Saturday)
Wire.write(decToBcd(dayOfMonth)); // set date (1 to 31)
Wire.write(decToBcd(month)); // set month
Wire.write(decToBcd(year)); // set year (0 to 99)
Wire.endTransmission();
}
void readDS3231time(byte *second,
byte *minute,
byte *hour,
byte *dayOfWeek,
byte *dayOfMonth,
byte *month,
byte *year)
{
Wire.beginTransmission(DS3231_I2C_ADDRESS);
Wire.write(0); // set DS3231 register pointer to 00h
Wire.endTransmission();
Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
// request seven bytes of data from DS3231 starting from register 00h
*second = bcdToDec(Wire.read() & 0x7f);
*minute = bcdToDec(Wire.read());
*hour = bcdToDec(Wire.read() & 0x3f);
*dayOfWeek = bcdToDec(Wire.read());
*dayOfMonth = bcdToDec(Wire.read());
*month = bcdToDec(Wire.read());
*year = bcdToDec(Wire.read());
}

void displayTime()
{
byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
// retrieve data from DS3231
readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month,
&year);
// send it to the serial monitor
Serial.print(hour, DEC);
// convert the byte variable to a decimal number when displayed
Serial.print(":");
if (minute<10)
{
Serial.print("0");
}
Serial.print(minute, DEC);
Serial.print(":");
if (second<10)
{
Serial.print("0");
}
Serial.print(second, DEC);
Serial.print(" ");
Serial.print(dayOfMonth, DEC);
Serial.print("/");
Serial.print(month, DEC);
Serial.print("/");
Serial.print(year, DEC);
Serial.print(" Day of week: ");
setTime(hour,minute,second,dayOfMonth,month,year);      // Ajuste l'heure de l'Arduino
switch(dayOfWeek){
case 1:
Serial.println("Sunday");
break;
case 2:
Serial.println("Monday");
break;
case 3:
Serial.println("Tuesday");
break;
case 4:
Serial.println("Wednesday");
break;
case 5:
Serial.println("Thursday");
break;
case 6:
Serial.println("Friday");
break;
case 7:
Serial.println("Saturday");
break;
}
}

void loop()
{
  // Controles de base
  
  if (firstStart == 0){
firstStart = 1;
Serial.println("Starting-Kalima-led");
Serial.println("Setting time");
displayTime();                                          // set the board time
int setdefault = setFfactoryDefault();                  // set the base programe
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
// Lecture de la valeures des channels dans la rom en fonction de l'heure
int getChannelValue(int pos, int ch){
pos = pos + (ch*24);
value = EEPROM.read(pos);
result = value;
Serial.println(result);
return result;
}
// Calcule du step par minute ( pos = heure de base / ch = cannal 0 - 3 )
int getChannelStep(int pos, int ch){
pos = pos + (ch * 24);
Serial.println(pos);
prevCh = EEPROM.read(pos);
pos = pos + 1;
Serial.println(prevCh);
if ( pos == (23 + (ch * 24)) )
{
pos = 0 + (ch * 24);
Serial.println(pos);
}
nextCh = EEPROM.read(pos);
Serial.println(pos);
Serial.println(nextCh);
delta = prevCh - nextCh;
Serial.println(delta);
result = delta / 60;
Serial.println(result);
return result;
}
// fonction LED OFF / ON
// fonction set LED according to channel value
// fonction set default programs params
int setFfactoryDefault(){
Serial.println("Factory default:");
for (i = 0; i < 24; i++){
addr = i;
Serial.println(addr);
value = ch1[i];
EEPROM.write(addr, value);
Serial.println(value);
addr = addr + 24;
value = ch2[i];
EEPROM.write(addr, value);
Serial.println(addr);
Serial.println(value);
addr = addr + 24;
value = ch3[i];
EEPROM.write(addr, value);
Serial.println(addr);
Serial.println(value);
addr = addr + 24;
value = ch4[i];
EEPROM.write(addr, value);
Serial.println(addr);
Serial.println(value);
}
}
