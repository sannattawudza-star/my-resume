#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <GxEPD2.h>
#include "GxEPD2_BW.h"
#include <Adafruit_GFX.h>
#include "GxEPD2_3C.h"
#include "FreeMonoBold9pt7b.h"
#include "free3of920pt7b.h"
#include "dw_font.h"    
#include <BarcodeGFX.h>
#include <WebServer.h>
#include <time.h>

const char* ssid = "official_new";        // ชื่อ Wi-Fi
const char* password = ""; // รหัสผ่าน Wi-Fi
const char* server_url = "http://110.49.142.178/Ternproject/send_to_epaper.php"; // URL ของเซิร์ฟเวอร์

IPAddress local_IP(192, 168, 30, 200);  // ตั้งค่า IP ที่ต้องการ
IPAddress gateway(192, 168, 30, 3);     // Gateway (ปกติจะเป็น Router)
IPAddress subnet(255, 255, 255, 0);    // Subnet Mask
IPAddress primaryDNS(8, 8, 8, 8);      // DNS หลัก
IPAddress secondaryDNS(8, 8, 4, 4);    // DNS สำรอง

#define SSID_ADDR 0          // ที่อยู่สำหรับ SSID
#define PASSWORD_ADDR 32     // ที่อยู่สำหรับ Password
#define CONNECT_TIMEOUT 10000 // เวลา Timeout (10 วินาที)

extern dw_font_info_t font_sarabun_20;
extern dw_font_info_t font_sarabun_32;
dw_font_t myfont;

#include "GxEPD2_display_selection.h"

BarcodeGFX barcode(display);

WebServer server(80); // สร้าง WebServer บนพอร์ต 80

unsigned long lastUpdateTime = 0;  // เวลาอัปเดตล่าสุด
const unsigned long updateInterval = 86400000;  // 1 นาที (1*60*1000 มิลลิวินาที)

int currentproductID;
String primaryUnitOfMeasure; // ตัวแปรเพื่อเก็บ primary_unit_of_measure
String stkcod; // ตัวแปรเพื่อเก็บ stkcod

void draw_pixel(int16_t x, int16_t y, uint16_t color) {
    display.drawPixel(x, y, color);
}

// ฟังก์ชันที่ใช้ในการเคลียร์พิกเซล
void clear_pixel(int16_t x, int16_t y) {
    display.drawPixel(x, y, GxEPD_WHITE);
}

String formatPrice(float price) {
    String priceStr = String(price, 2);
    int dotIndex = priceStr.indexOf('.');
    int insertPosition = dotIndex - 3;
    while (insertPosition > 0) {
        priceStr = priceStr.substring(0, insertPosition) + ',' + priceStr.substring(insertPosition);
        insertPosition -= 3;
    }
    return priceStr;
}

String extractThaiFirst(const String& input) {
    const char* thaiChars = "กขฃคฅฆงจฉชซฌญฎฏฐฑฒณดตถทธนบปผฝพฟภมยรฤลฦวศษสหฬอฮฯะัาำิีึืุูเแโใไๅๆ็่้๊๋์";
    int thaiStart = -1;
    for (int i = 0; i < input.length(); ++i) {
        if (strchr(thaiChars, input[i])) {
            thaiStart = i;
            break;
        }
    }
    if (thaiStart != -1) {
        return input.substring(thaiStart);
    }
    return input;
}

void displayProductInfo(const char* description, float price, const char* primary_unit_of_measure, const char* changeDate, const char* stkcod) {
    // แสดงเฉพาะส่วนแรกของชื่อสินค้า
    display.fillScreen(GxEPD_WHITE);
    display.setTextColor(GxEPD_BLACK);
    String shortDescription = extractThaiFirst(String(description));
    String firstLine, secondLine;
    
    // ตรวจสอบความยาวของบรรทัดแรก

    if(shortDescription.length() <= 60) {
        firstLine = shortDescription.substring(0, 60);
        dw_font_setfont(&myfont, &font_sarabun_32);
        dw_font_goto(&myfont, 5, 26);
        dw_font_print(&myfont, const_cast<char*>(firstLine.c_str()), GxEPD_BLACK);
        
        dw_font_goto(&myfont, 5, 65);
        dw_font_setfont(&myfont, &font_sarabun_32);
        dw_font_print(&myfont, ("ราคา:" + formatPrice(price) + " บาท/" + String(primary_unit_of_measure)).c_str(), GxEPD_BLACK);
        
        dw_font_goto(&myfont, 0, 122);
        dw_font_setfont(&myfont, &font_sarabun_20);
        dw_font_print(&myfont, ("ราคาเมื่อวันที่: " + String(changeDate)).c_str(), GxEPD_BLACK);
    }
    else{
        firstLine = shortDescription.substring(0, 56);
        secondLine = shortDescription.substring(56, 100);
        dw_font_setfont(&myfont, &font_sarabun_32);
        dw_font_goto(&myfont, 5, 26);
        dw_font_print(&myfont, const_cast<char*>(firstLine.c_str()), GxEPD_BLACK);
        dw_font_goto(&myfont, 5, 62);
        dw_font_print(&myfont, const_cast<char*>(secondLine.c_str()), GxEPD_BLACK);
        dw_font_goto(&myfont, 0, 95);
        dw_font_setfont(&myfont, &font_sarabun_20);
        dw_font_print(&myfont, ("ราคา:" + formatPrice(price) + " บาท/" + String(primary_unit_of_measure)).c_str(), GxEPD_BLACK);

        dw_font_goto(&myfont, 0, 122);
        dw_font_setfont(&myfont, &font_sarabun_20);
        dw_font_print(&myfont, ("ราคาเมื่อวันที่: " + String(changeDate)).c_str(), GxEPD_BLACK);
}
}

void fetchProductData(int productId) {
    WiFiClient client;  // สร้าง WiFiClient
    HTTPClient http;
    
    Serial.println("Connecting to: " + String(server_url));
    
    http.begin(client, server_url);
    http.setUserAgent("ESP32");  // ป้องกันการถูกบล็อกจากบางเซิร์ฟเวอร์
    http.addHeader("Content-Type", "application/json");

    // สร้าง JSON payload
    String jsonPayload = "{\"product_id\":" + String(productId) + "}";
    int httpResponseCode = http.POST(jsonPayload);

    if (httpResponseCode > 0) {
        String payload = http.getString();
        Serial.println("HTTP Response code: " + String(httpResponseCode));
        Serial.println("Response: " + payload);  // ตรวจสอบ JSON ที่ได้รับ

        StaticJsonDocument<1024> doc;
        DeserializationError error = deserializeJson(doc, payload);

        if (error) {
            Serial.println("Error parsing JSON");
            return;
        }

        // ตรวจสอบว่า JSON มีค่าที่ต้องการหรือไม่
        if (!doc.containsKey("description") || !doc.containsKey("prc01") || !doc.containsKey("chgdat") || !doc.containsKey("primary_unit_of_measure") || !doc.containsKey("stkcod")) {
            Serial.println("ERROR: JSON format incorrect or missing keys");
            return;
        }

        const char* description = doc["description"];
        float prc01 = doc["prc01"];
        const char* chgdat = doc["chgdat"];
        primaryUnitOfMeasure = String((const char*)doc["primary_unit_of_measure"]); // เก็บค่า primary_unit_of_measure ในตัวแปร
        stkcod = String((const char*)doc["stkcod"]); // เก็บค่า stkcod ในตัวแปร

        Serial.println("Parsed JSON:");
        Serial.println("Description: " + String(description));
        Serial.println("Price: " + String(prc01));
        Serial.println("Date: " + String(chgdat));
        Serial.println("Unit: " + primaryUnitOfMeasure);
        Serial.println("Stock Code: " + stkcod);

        // --- แสดงผลบน e-paper ---
        dw_font_init(&myfont, display.epd2.WIDTH, display.epd2.HEIGHT, draw_pixel, clear_pixel);
        display.setTextColor(GxEPD_BLACK);
        display.setFullWindow();

        display.firstPage();
        do {
            display.fillScreen(GxEPD_WHITE);
            displayProductInfo(description, prc01, primaryUnitOfMeasure.c_str(), chgdat, stkcod.c_str());
        } while (display.nextPage());

        display.display();
    } else {
        Serial.printf("Error on HTTP request: %d\n", httpResponseCode);
    }

    http.end();
}

void handleRoot() {
    server.sendHeader("Access-Control-Allow-Origin", "*"); // เพิ่มการตั้งค่า CORS
    server.send(200, "text/plain", "Hello from ESP32!");
    if (server.hasArg("product_id") && server.hasArg("primary_unit_of_measure") && server.hasArg("stkcod")) {
        currentproductID = server.arg("product_id").toInt();
        primaryUnitOfMeasure = server.arg("primary_unit_of_measure");
        stkcod = server.arg("stkcod");
        fetchProductData(currentproductID);
        server.send(200, "application/json", "{\"message\": \"Product data fetched and displayed.\"}"); // ส่ง JSON ที่ถูกต้อง
    } else {
        server.sendHeader("Access-Control-Allow-Origin", "*"); // เพิ่มการตั้งค่า CORS
        server.send(400, "application/json", "{\"error\": \"Missing product_id, primary_unit_of_measure, or stkcod parameter.\"}"); // ส่ง JSON ที่ถูกต้อง
    }
}

void connectToWiFi() {
    Serial.begin(115200);  // เริ่มการสื่อสารผ่าน Serial
    Serial.println("Connecting to WiFi...");
  
    WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS); // ตั้งค่า Static IP
    WiFi.begin(ssid, password); // เริ่มการเชื่อมต่อกับ Wi-Fi
  
    while (WiFi.status() != WL_CONNECTED) {  // ตรวจสอบสถานะการเชื่อมต่อ
        delay(1000);  // รอ 1 วินาที
        Serial.println("Connecting...");
    }
  
    Serial.println("Connected to WiFi!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());  // แสดง IP ที่ได้จากการเชื่อมต่อ

    // แสดงบาร์โค้ดทันทีเมื่อเชื่อมต่อ Wi-Fi
}

void setup() {
    uint32_t dt = millis();
    display.init();
    display.setRotation(1);
    display.setFullWindow();
    display.fillScreen(GxEPD_WHITE);
    Serial.begin(115200);
    connectToWiFi();  // เชื่อมต่อ Wi-Fi

    server.on("/", handleRoot);
    server.begin();
    Serial.println("HTTP server started");

    lastUpdateTime = millis();  // บันทึกเวลาเริ่มต้น

    // ตั้งค่า NTP เพื่อซิงค์เวลา
    configTime(25200, 0, "pool.ntp.org", "time.nist.gov"); // 25200 คือ offset เวลาของประเทศไทย (GMT+7)
}

void loop() {
    server.handleClient();  // จัดการคำขอ HTTP

    // ดึงเวลาปัจจุบัน
    time_t now = time(nullptr);
    struct tm* timeinfo = localtime(&now);

    // เช็คว่าถึงเวลา 02:00 ของเวลาประเทศไทยหรือยัง
    if (timeinfo->tm_hour == 2 && timeinfo->tm_min == 0 && (millis() - lastUpdateTime) >= 60000) {
        Serial.println("It's 02:00, updating product data...");
        fetchProductData(currentproductID);  // ดึงข้อมูลสินค้าจากเซิร์ฟเวอร์
        lastUpdateTime = millis();  // รีเซ็ตเวลา
    }
}