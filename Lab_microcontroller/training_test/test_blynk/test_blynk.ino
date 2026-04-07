  //Blynk Loop
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#define led1 14
#define led2 15
#define led3 0
#define led4 4
#define ldr   36
#define sw1 16
const char ssid[] = "Leng";
const char pwd[]  = "11111111";
#define BLYNK_SERVER  "blynk.cloud"
#define BLYNK_TEMPLATE_ID "TMPLrVNxF-m4"
#define BLYNK_DEVICE_NAME "nattawud"
#define BLYNK_AUTH_TOKEN "iZJXAdN-BMTIJg9Ne2tTD6vvn65wKNmy"
BlynkTimer  myTimer;
void sendSensor(void){
  int adc = analogRead(ldr);
  Serial.println(adc);
  Blynk.virtualWrite(V0,adc);
    if(adc<=1200){
    digitalWrite(led1, HIGH);
    digitalWrite(led2,LOW);
    digitalWrite(led3,LOW);
    digitalWrite(led4,LOW);
  }
  else if(adc<=2000){
    digitalWrite(led1, LOW);
    digitalWrite(led2,HIGH);
    digitalWrite(led3,LOW);
    digitalWrite(led4,LOW);
  }
  else if(adc<=3000){
    digitalWrite(led1, LOW);
    digitalWrite(led2,LOW);
    digitalWrite(led3,HIGH);
    digitalWrite(led4,LOW);
  }
  else if(adc>4000){
    digitalWrite(led1, LOW);  
    digitalWrite(led2,LOW);
    digitalWrite(led3,LOW);
    digitalWrite(led4,HIGH);
  }
}
void control(int val){
  if(val==1){
    digitalWrite(led1, HIGH);
  }
  else{
    digitalWrite(led1, LOW);
  }
}
void control2(int val2){
  if(val2==1){
    digitalWrite(led2, HIGH);
  }
  else{
    digitalWrite(led2, LOW);
  }
}
void control3(int val3){
  if(val3==1){
    digitalWrite(led3, HIGH);
  }
  else{
    digitalWrite(led3, LOW);
  }
}
void control4(int val4){
  if(val4==1){
    digitalWrite(led4, HIGH);
  }
  else{
    digitalWrite(led4, LOW);
  }
}
BLYNK_WRITE(V1){
  int value = param.asInt();
  control(value);
}
BLYNK_WRITE(V2){
  int value2 = param.asInt();
  control2(value2);
}
BLYNK_WRITE(V3){
  int value3 = param.asInt();
  control3(value3);
}
BLYNK_WRITE(V4){
  int value4 = param.asInt();
  control4(value4);
}
void setup() {
  Serial.begin(115200);
  pinMode(led1, OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4,OUTPUT);
  digitalWrite(led1, HIGH);
  digitalWrite(led2,HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4,HIGH);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pwd, BLYNK_SERVER);
  myTimer.setInterval(2000L, sendSensor);
  Serial.println("Test Blynk");
}
void loop() {
  Blynk.run();
  myTimer.run();
}
