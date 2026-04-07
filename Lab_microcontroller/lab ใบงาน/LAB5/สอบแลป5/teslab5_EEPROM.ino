#include<EEPROM.h>
#define sw1 14
#define sw2 12
#define sw3 13
#define sw4 26
#define sw5 25

int sec1,sec2,i,x,savetime1,savetime2,alltime1,alltime2;
byte addr,Data,Data2;
unsigned long timer=0;
void setup() {
  pinMode(sw1,INPUT); //ตัวเริ่ม หยุด
  pinMode(sw2,INPUT); //ตัวขวา
  pinMode(sw3,INPUT); //ตัวซ้าย
  pinMode(sw4,INPUT); //ตัวซ้าย
  pinMode(sw5,INPUT); //ตัวซ้าย
  EEPROM.begin(512);
  Serial.begin(115200);
  Serial.println("เลือกเครื่องจักร");
}

void loop() {
    if(digitalRead(sw2)==1){
      Serial.println("เลือกเครื่องจักที่1"); 
      x=1; 
      delay(500);
    }
    else if(digitalRead(sw3)==1){
            Serial.println("เลือกเครื่องจักที่2"); 
            x=2;
            delay(500); 
   }
      if(digitalRead(sw4)==1){ //อ่านค่าทั้งหมดของเครื่องจักร1
      Serial.print("เวลาทำงานของเครื่อง1 = ");
      Serial.print(savetime1);
      Serial.println(" ");
      Serial.print("เวลาทำงานของเครื่อง2 = ");
      Serial.print(savetime2);
      Serial.println(" ");
      delay(500);
}
   if(x==1){
      if(digitalRead(sw1)==1){ //ปุ่มกดทำงาน
      Serial.println("เครื่องจักรกำลังทำงาน");
      i=1;
      delay(500);
   }
    if(i==1){  //เวลาเริ่มนับ
      sec1++;
      delay(1000);
      if(digitalRead(sw1)==1){ //ปุ่มหยุดทำงาน
        i=2;

      }
        if(i==2){  //หยุดเครื่องจักร1
            alltime1+=sec1;
            EEPROM.write(1,alltime1);
            EEPROM.commit();
            savetime1=EEPROM.read(1);///////
            EEPROM.write(3,sec1);
            Data=EEPROM.read(3);
            Serial.print("เวลาที่ทำงาน = ");
            Serial.print(Data);
            Serial.print("\t วินาที");
            Serial.println(""); 
            sec1=0;
            sec2=0;
            i=0;
            delay(1000);
            
    }
    }
  }
  if(x==2){ //////////เครื่อง2
      if(digitalRead(sw1)==1){ //ปุ่มกดทำงาน
      Serial.println("เครื่องจักรกำลังทำงาน");
      i=2;
      delay(500);
   }
    if(i==2){  //เวลาเริ่มนับ
      sec2++;
      delay(1000);
      if(digitalRead(sw1)==1){ //ปุ่มหยุดทำงาน
        i=3;
      }
        if(i==3){  //หยุดเครื่องจักร2
            alltime2+=sec2;
            EEPROM.write(2,alltime2);
            EEPROM.write(4,sec2);
            EEPROM.commit();
            savetime2=EEPROM.read(2); //อ่านแสดงหลังกด
            Data2=EEPROM.read(4);
            Serial.print("เวลาที่ทำงาน = ");
            Serial.print(Data2);
            Serial.print("\t วินาที");
            Serial.println(""); 
            i=0;
            sec1=0;
            sec2=0;
            delay(1000);
}
    }
  }
}
