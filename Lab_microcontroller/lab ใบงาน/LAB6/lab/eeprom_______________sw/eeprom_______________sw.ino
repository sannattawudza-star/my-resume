#include<EEPROM.h>
#define readMode 6
#define writeMode 7
int addrR = 0;
int addrW = 0;
byte data;
void setup() 
{
pinMode(readMode,INPUT);
 pinMode(writeMode,INPUT);
 Serial.begin(9600);
}
void loop() {
if(digitalRead(readMode) == 0 )
{
 delay(150);
 data = EEPROM.read(0);
 Serial.print("Address");
 Serial.print(addrR,HEX);
 Serial.print(" : ");
 Serial.println(data);
 if(addrR<255) addrR++;
 else addrR = 0;
 delay(500);
}
 if(digitalRead(writeMode) == 0 )
 {
 delay(150);
 data++;
 if(data<256) EEPROM.write(0,data);
 else data = 0;
 Serial.print("Address");
 Serial.print(addrW,HEX);
 Serial.print(" : ");
 Serial.println(data);
 if(addrW<255) addrW++;
 else addrW = 0;
 delay(500);
 }
}
