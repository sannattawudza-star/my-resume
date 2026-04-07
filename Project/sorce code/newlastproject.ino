#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>

const int pirPin = 4;
Servo myservo;

const char* ssid = "Yodmanee55_2.4GHz";
const char* password = "Yodmanee555";

WebServer server(80);

void servostart() {
  myservo.write(90);  
   Serial.println("[DEBUG] Finished myservo.write(90)");
}
void handleServoStart() {
  Serial.println("🔧 Servo activated via web!");
  servostart();
  server.send(200, "text/plain", "Servo started");
}


void handleRoot() {
  server.send(200, "text/plain", "ESP32 WebServer is running!");
}
void setup() {
  Serial.begin(115200);
  pinMode(pirPin, INPUT);
    myservo.attach(14);
Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi connected. IP:");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/servostart", HTTP_POST, handleServoStart);
  server.begin();
  Serial.println("✅ Web server started.");
}
void loop() {
    int motionDetected = digitalRead(pirPin);
  server.handleClient();
     if (motionDetected == 1) {
      Serial.println("🔴 Motion Detected!");
      myservo.write(25);  // ปิดหรือยกลง
    } else {
      Serial.println("⚪️ Motion Ended.");
    }
}