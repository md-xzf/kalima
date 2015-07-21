

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
