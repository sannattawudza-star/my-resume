#include <WiFi.h>
#include <GxEPD.h>
#include <GxDEPG0213BN/GxDEPG0213BN.h>    // 2.13" b/w 128x250, SSD1680, TTGO T5 V2.4.1, V2.3.1
#include <Fonts/FreeMonoBold9pt7b.h>

#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>
#if defined(ESP32)
GxIO_Class io(SPI, SS, /*DC=*/ 17, /*RST=*/ 16); // ตั้งค่าพินสำหรับ ESP32
GxEPD_Class display(io, /*RST=*/ 16, /*BUSY=*/ 4); // ตั้งค่าพินสำหรับ ESP32
#endif

const char ssid[] = "ihone";
const char pwd[]  = "123456789000";

unsigned long previousMillis = 0;  // ตัวแปรเก็บเวลาที่ผ่านไป
const long interval = 60000;  // 10 นาที (600,000 มิลลิวินาที)

void setup() {
  Serial.begin(115200);
  connectWiFi();
    display.init(115200); // เปิดการดีบักผ่าน Serial

}

void loop() {
  unsigned long currentMillis = millis();
  
  // ถ้าผ่านไป 1 นาที (600000 มิลลิวินาที)
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    connectWiFi();  // เชื่อมต่อ Wi-Fi ใหม่
    drawHeart();
    display.update();   // อัพเดตหน้าจอ
    display.powerDown();  // ปิดหน้าจอเมื่อเสร็จ      
    resetWiFi();
  }  // รีเซ็ต Wi-Fi

  // ส่วนอื่นๆ ของโค้ดที่ต้องการให้ทำใน loop
}
void drawHeart() {
  display.setRotation(1);  // หมุนหน้าจอ
  display.fillScreen(GxEPD_WHITE);  // เติมหน้าจอเป็นสีขาว
  
  // วาดรูปหัวใจ
  // วาดวงกลมซ้ายบน
  display.fillCircle(40, 50, 20, GxEPD_BLACK);  // วงกลมซ้าย
  // วาดวงกลมขวาบน
  display.fillCircle(60, 50, 20, GxEPD_BLACK);  // วงกลมขวา
  
  // วาดสามเหลี่ยมด้านล่างของหัวใจ
  display.fillTriangle(22, 60, 78.5, 60, 50, 90, GxEPD_BLACK);  // รูปสามเหลี่ยมด้านล่างของหัวใจ
  
  display.setTextColor(GxEPD_BLACK);  // เลือกสีข้อความเป็นสีดำ
  display.setFont(&FreeMonoBold9pt7b);  // เลือกฟอนต์
  
  // เพิ่มข้อความใต้หัวใจ
  display.setCursor(30, 120);
  display.print("KHAWFANG");  // ข้อความ "Love"
}
void connectWiFi() {
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, pwd);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(50);
  }
  Serial.println("WiFi Connected");
  Serial.println(WiFi.localIP());
}

void resetWiFi() {
  Serial.println("Disconnecting WiFi...");
  WiFi.disconnect();  // ทำการตัดการเชื่อมต่อ Wi-Fi
  delay(1000);  // รอ 1 วินาที
  Serial.println("WiFi Disconnected");
}
