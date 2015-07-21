int time1=0;
int time2=0;
int programSelect=0;
float channel1=0;
float channel2=0;
float channel3=0;
float channel4=0;
float drive1=0;
float drive2=0;
float drive3=0;
float drive4=0;
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
float channel1Step=0;
float channel2Step=0;
float channel3Step=0;
float channel4Step=0;
float result;
float delta;
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
File myFile;
