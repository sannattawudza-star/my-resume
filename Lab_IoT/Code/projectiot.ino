#include <TridentTD_LineNotify.h>
#define ssmoke 34
#define relay 4
#define ssound 12
bool oldstate = LOW;

#define SSID        "Luvsan"      
#define PASSWORD    "11111111"     
#define LINE_TOKEN  "dczSvFsWnuyMdQMWsCuv3fZ9ftVckpbL41fV8km7HOX"   // บรรทัดที่ 13 ใส่ รหัส TOKEN ที่ได้มาจากข้างบน

unsigned long period = 1000; 
unsigned long last_time = 0; 

void setup() {
  Serial.println(LINE.getVersion());
  pinMode(ssmoke, INPUT);
  pinMode(ssound, INPUT);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW);
  Serial.begin(9600);
  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n",  SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(400);
  }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());
  LINE.setToken(LINE_TOKEN);
}
void loop() {
  bool newstate = digitalRead(ssound);
  int smk = analogRead(ssmoke);
  Serial.println(smk);
  if (newstate == HIGH && oldstate == LOW) {
    digitalWrite(relay, !digitalRead(relay));
  }
  oldstate = newstate;
  delay(60);
  if( millis() - last_time > period) {
    if(smk>1100){
    LINE.notify("ตรวจพบแก๊ส,ควันผิดปกติในห้อง");
     last_time = millis(); 
    }
  }
}