  //Blynk Loop
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#define relay 0
#define ldr   34
#include <LiquidCrystal_I2C.h> // ไลบรารี่เพื่อใช้งานหน้าจอ LCD
#include <TridentTD_LineNotify.h> // ไลบรารี่เพื่อใช้งานไลน์ Notify 
LiquidCrystal_I2C lcd(0x27, 16,2); //ตั้งค่าLCD ให้มีชื่อว่า lcd
//const int A = analogRead(36); //กำหนดขา Analog สำหรับขาของ MQ-02
int sensorValue = 0; //ค่าควันที่ตรวจจับ
int outputValue = 0; //ค่าควันที่แสดงผลออกผ่านหน้าจอLCD
#define LINE_TOKEN  "WPU5ZHRxcmgKCwjR0iFhSfwuzY0fRWEJ5Y8YLhaKdEB" //Token ที่ออกจากเว็บไซต์ line notify
//////////////////
const char ssid[] = "myIphone"; // ชื่อWIFI
const char pwd[]  = "123456789000";// รหัส WIFI
#define BLYNK_SERVER  "blynk.cloud" //เขื่อมต่อ Cloud ของ Blynk
#define BLYNK_TEMPLATE_ID "TMPLrVNxF-m4"
#define BLYNK_DEVICE_NAME "nattawud" //ตั้งค่าชื่อ Device ใน Blynk
#define BLYNK_AUTH_TOKEN "iZJXAdN-BMTIJg9Ne2tTD6vvn65wKNmy"
BlynkTimer  myTimer;
void sendSensor(void){ //ฟังก์ชัน ส่งค่าแสงไปยัง blynk
  int adc = analogRead(ldr); //เก็บค่าของแสงไว้ในตัวแปร adc
  Serial.println(adc); //แสดงค่าของแสงบนมอนิเตอร์
  Blynk.virtualWrite(V0,adc); ส่งค่าของแสงไปยังVO ของBlynk
  }
void control(int val){ //ฟังก์ชันควบคุมการเปิดปิดบน Blynk
  if(val==1){
    digitalWrite(relay, HIGH);
  }
  else{
    digitalWrite(relay, LOW);
  }
}
BLYNK_WRITE(V1){ //ฟังก์ชันการส่งค่าไปยัง V1 ของอุปกรณ์ในBlynk
  int value = param.asInt();
  control(value);
}
void setup() {
  lcd.begin(); //เริ่มต้นใช้งาน หน้าจอ LCD
  lcd.backlight();
  lcd.setCursor(0, 0); //เซ็ตตำแหน่งของLCDอยู่ที่0 บรรทัดที่1
  Serial.begin(115200);
  WiFi.begin(ssid, pwd); // เชื่อมต่อ Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000); // หน่วงเวลา 1000/ms
    Serial.print(".");
  }
  Serial.println(""); 
  Serial.println("WiFi connected");
  LINE.setToken(LINE_TOKEN);  //เชื่อมต่อกับ TOKEN LINE
  pinMode(relay, OUTPUT); //set relay เป็น OUTPUT
  digitalWrite(relay, HIGH); //relayทำงานที่ ตรรกะสูง
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pwd, BLYNK_SERVER); //คำสั่งให้blynkเชื่อมต่อWIFI
  myTimer.setInterval(2000L, sendSensor); 
  Serial.println("Test Blynk");
}
void loop() { //ฟังก์ชันให้blynkและหน้าจอ LCD ทำงานแบบเรียลไทม์ 
  Blynk.run();
  myTimer.run();
  sensorValue = analogRead(36);
  outputValue = map(sensorValue, 0, 1023, 0, 100);
  Serial.println(outputValue);
  if (outputValue >= 100) { //คำสั่งที่กำหนดค่าของควัน
     LINE.notify("แจ้งเตือน : ตรวจพบควันเกินค่าที่กำหนด !!");
      Serial.println(outputValue); 
        lcd.setCursor(0, 0);
        lcd.print("Detect Value=");
        lcd.print(outputValue); //แสดงผลที่ตรวจจับผ่านหน้าจอLCD
        delay(250);
      }
  else {
        lcd.setCursor(0, 0);
        lcd.print("Detect Value =");
        lcd.print(outputValue);
        delay(250);
        }
}
