#include <SoftwareSerial.h>


/*
 * Kalima-led
 *
 * Read value from serial and set rom acordigly
 * Read rom according to time
 */

int time1=0;
int time2=0;
int program_select=0;
int channel1=0;
int channel2=0;
int channel3=0;
int channel4=0;
int drive1=0;
int drive2=0;
int drive3=0;
int drive4=0;
int first_start=0;
int time_start=0;
int duration=0;
int set_program=0;
int heure=0;
int past_hour = 0;
int minuts=0;
int laste_minute=0;
int serial_read=0;
int new_data=0;
int address = 0;
byte value;
int state=0;
int past_time=0;
int ch1_prev=0;
int ch1_next=0;
int ch2_prev=0;
int ch2_next=0;
int ch3_prev=0;
int ch3_next=0;
int ch4_prev=0;
int ch4_next=0;
int channel1_step=0;
int channel2_step=0;
int channel3_step=0;
int channel4_step=0;
int ch=0;
int drivPin1 = 10;
int drivPin2 = 9;
int drivPin3 = 6;
int drivPin4 = 5;

#include <EEPROM.h>
#include <Time.h>



void setup()
{
   pinMode(drivPin1, OUTPUT);
   pinMode(drivPin2, OUTPUT);
   pinMode(drivPin3, OUTPUT);
   pinMode(drivPin4, OUTPUT);
  // initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
}

void loop()
{

  if (Serial.available()) {
    serial_read = Serial.read();
    new_data=1;
  }

  heure = hour();
  minuts = minute();
  

  if (past_hour =! heure){  
    
    // get new channels value
    channel1 = get_channel_value(heure, 0);
    channel2 = get_channel_value(heure, 1);
    channel3 = get_channel_value(heure, 2);
    channel4 = get_channel_value(heure, 3);
    
    channel1_step = get_channel_step(heure, 0);
    channel2_step = get_channel_step(heure, 1);
    channel3_step = get_channel_step(heure, 2);
    channel4_step = get_channel_step(heure, 3);
    past_hour = heure;
   

  }
  
  
  if (laste_minute =! minuts)
  { 
    drive1 = channel1 + (minuts * channel1_step);
    drive2 = channel2 + (minuts * channel2_step);
    drive3 = channel3 + (minuts * channel3_step);
    drive4 = channel4 + (minuts * channel4_step);
    
    analogWrite(drivPin1, drive1);
    analogWrite(drivPin2, drive2);
    analogWrite(drivPin3, drive3);
    analogWrite(drivPin4, drive4); 

  laste_minute = minuts;

  }

}

// Lecture de la valeures des channels dans la rom en fonction de l'heure

int get_channel_value(int pos, int ch){
    int value;
    pos = pos + (ch*24);
    value = EEPROM.read(pos);
    int result;
    result = value;
    return result;
  }


// Calcule du step par minute ( pos = heure de base / ch = cannal 0 - 3 )

  int get_channel_step(int pos, int ch){
    int prev_ch;
    int next_ch;
    pos = pos + (ch*24);
    prev_ch = EEPROM.read(pos);
    pos = pos ++;
    if (pos = (24 + (ch * 24))){ 
      pos = 0;
    }
    next_ch = EEPROM.read(pos);
    int result;
    result = (prev_ch - next_ch) / 60;
    return result;
  }
  
  // fonction LED  OFF / ON
  
  // fonction set LED according to channel value 
  
  // fonction set default programs params
  
  int set_factory_default(){
    int ch1[24] = 0, 0, 0, 0, 0, 0, 0, 20, 60, 120, 255, 255, 200, 180, 160, 120, 80, 60, 20, 0, 0, 0, 0, 0;
    int ch2[24] = 0, 0, 0, 0, 0, 0, 0, 20, 60, 120, 255, 255, 200, 180, 160, 120, 80, 60, 20, 0, 0, 0, 0, 0;
    int ch3[24] = 0, 0, 0, 0, 0, 0, 0, 20, 60, 120, 255, 255, 200, 180, 160, 120, 80, 60, 20, 0, 0, 0, 0, 0;
    int ch4[24] = 0, 0, 0, 0, 0, 0, 0, 20, 60, 120, 255, 255, 200, 180, 160, 120, 80, 60, 20, 0, 0, 0, 0, 0;
    
    int i;
    for (i = 0, i < 24; i = i + 1){
      
    addr = i;
    value = ch1[i];
    EEPROM.wright(addr, value);
    value = ch2[i];
    EEPROM.wright(addr, value);
    value = ch3[i];
    EEPROM.wright(addr, value);
    value = ch4[i];
    EEPROM.wright(addr, value);
    
    }
    
    
