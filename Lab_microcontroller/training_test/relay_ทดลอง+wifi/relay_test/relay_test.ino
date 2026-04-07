  //Blynk Loop
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#define relay 0
#define ldr   36
const char ssid[] = "Thememmo_2.4G";
const char pwd[]  = "0818964699Z";
#define BLYNK_SERVER  "blynk.cloud"
#define BLYNK_TEMPLATE_ID "TMPLrVNxF-m4"
#define BLYNK_DEVICE_NAME "nattawud"
#define BLYNK_AUTH_TOKEN "iZJXAdN-BMTIJg9Ne2tTD6vvn65wKNmy"
BlynkTimer  myTimer;
void sendSensor(void){
  int adc = analogRead(ldr);
  Serial.println(adc);
  Blynk.virtualWrite(V0,adc);
  }
void control(int val){
  if(val==1){
    digitalWrite(relay, HIGH);
  }
  else{
    digitalWrite(relay, LOW);
  }
}
BLYNK_WRITE(V1){
  int value = param.asInt();
  control(value);
}
void setup() {
  Serial.begin(115200);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pwd, BLYNK_SERVER);
  myTimer.setInterval(2000L, sendSensor);
  Serial.println("Test Blynk");
}
void loop() {
  Blynk.run();
  myTimer.run();
}
