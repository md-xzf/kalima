#include <EEPROM.h>
#include <Time.h>

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
  Serial.begin(9600);

}

void loop()
{



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
  if (firstStart == 0){
    firstStart = 1;
    Serial.println("Starting-Kalima-led");


    int setdefault = setFfactoryDefault();

  }
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

// fonction LED  OFF / ON

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




