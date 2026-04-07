#include "Wire.h"
#include <EEPROM.h>
#include "SPI.h"  // not used here, but needed to prevent a RTClib compile error
#include "RTClib.h"
RTC_DS3231 RTC;
String Y,M,D,H,MI,S,alltime;
void setup () {
  Serial.begin(9600);
  Wire.begin();
  RTC.begin();
  EEPROM.begin(512);
    RTC.adjust(DateTime(__DATE__, __TIME__));
}

void loop () {
  DateTime now = RTC.now();
  Y=now.year();
  M=now.month();
  D=now.day();
  H=now.hour();
  MI=now.minute();
  S=now.second();
  alltime=" DATE "+String(Y)+'/'+String(M)+'/'+String(D)+" TIME "+String(H)+':'+String(MI)+':'+String(S);
  int a=alltime.toInt();
  EEPROM.write(1,a);
  EEPROM.read(1);
  Serial.print(alltime);
  Serial.println();
  delay(1000);

}
