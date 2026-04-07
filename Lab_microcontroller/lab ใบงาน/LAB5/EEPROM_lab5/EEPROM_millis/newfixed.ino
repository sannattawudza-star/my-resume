#include<EEPROM.h>
unsigned long timer=0;
int Sec,Min=59,Hour=23;
int Day=1,Month=1,Year=2022;
int ED,EM,EY,Esec,Emin,Ehour;
void setup() {
  Serial.begin(115200);
}

void loop() {
   if(millis()-timer>=1000){  //วินาที
    Sec+=1;
    timer+=1000;
    EEPROM.write(1,Sec);
    if(Sec>=60){  //นาที
      Sec=0;
      Min+=1;
      EEPROM.write(2,Min);
      if(Min>=60){ //ชั่วโมง
        Min=0;
        Hour+=1;
        EEPROM.write(3,Hour);
        if(Hour>=24){ //วัน
          Hour=0;
          Day+=1;
          EEPROM.write(4,Day);
          if(Day>=30){ //เดือน
            Day=1;
            Month+=1;
            EEPROM.write(5,Month);
            if(Month>=12){ //ปี
              Month=1;
              Year+=1;
              EEPROM.write(6,Year);
            }
          }
        }
      }
    }
   }
   EEPROM.read(6);
   EEPROM.read(5);
   EEPROM.read(4);
   EEPROM.read(3);
   EEPROM.read(2);
   EEPROM.read(1);
   ///วัน
   Serial.print("Date \t");
   Serial.print(Day);
   Serial.print("/");
   Serial.print(Month);
   Serial.print("/");
   Serial.print(Year);
   ///////เวลา
   Serial.print("\t Time \t");
   Serial.print(Hour);
   Serial.print(":");
   Serial.print(Min);
   Serial.print(":");
   Serial.print(Sec);
   Serial.println(" ");
   delay(1000);   
}
