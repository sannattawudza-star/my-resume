int led[] = {16, 17, 18, 19, 21, 22, 23};
#define sw 14
int i;
bool state = true;
unsigned long Time = 0;
 unsigned long Time2 = 0;
void setup() {
  for ( i = 0; i <= 6; i++)
  {
    pinMode(led[i], OUTPUT);
    digitalWrite(led[i], 1);
  }
  pinMode(sw, INPUT);
  Serial.begin(115200);
}
void loop() {
 int a = digitalRead(sw);
    if(a==1){
      state = !state;
    for( i=0;i<=6;i++){
    digitalWrite(led[i],state);
    delay(1000);
      }
    }// int a = digitalRead(sw);
     if(a==1 && millis() - Time >= 2000){
     Time +=2000;
      for ( i = 0; i <= 6; i++){
      digitalWrite(led[i], 1);
  }
}
}
