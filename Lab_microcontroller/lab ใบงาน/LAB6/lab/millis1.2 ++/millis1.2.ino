int led[] = {16, 17, 18, 19, 21, 22, 23};
#define sw 14
int i;
  int x=0;
bool state = false;
unsigned long Time1 = 0;
unsigned long Time2 = 0;
void setup() {
  for (int i = 0; i <= 6; i++)
  {
    pinMode(led[i], OUTPUT);
    digitalWrite(led[i], 1);
  }
  pinMode(sw, INPUT);
  Serial.begin(115200);
}
void loop() {
   for (int i = 0; i <= 6; i++)
  {
    digitalWrite(led[i], 0);
}
if(digitalRead(14)==1){
  Time2 += 1000;
  if(millis()-Time2>=2000){
    for (int i = 0; i <= 6; i++)
  {
    digitalWrite(led[i], 1);
}
  }
}
}
