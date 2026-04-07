int i = 0;
int sw1;
int led[] = {16, 17, 18, 19, 21, 22, 23};
int led_status = 0 ;
void setup() {
  for (i = 0; i <= 6; i++) {
    pinMode(led[i], OUTPUT);
    digitalWrite(led[i], 1);
  } pinMode(sw, INPUT) ;
  Serial.begin(115200);
}
void loop() {
  sw1 = digitalRead(D0);
  if (sw1 == 1) {
    delay(250);
    for (i = 0 ; i < 6 && led_status == 0 ; i++) {
      Serial.println(digitalRead(D0));
      digitalRead(sw);
      if (digitalRead(sw) == 1) {
        led_status = 1 ;
      } else {
        digitalWrite(led[i], 0);
        delay(1000);
      }
    }
  }
}
