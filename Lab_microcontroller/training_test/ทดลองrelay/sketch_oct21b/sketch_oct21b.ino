#define relay 0
void setup() {
  Serial.begin(115200);
  pinMode(relay,OUTPUT);
  digitalWrite(relay,HIGH);
  Serial.begin(115200);
  // put your setup code here, to run once:

}

void loop() {
    int i=analogRead(36);
    if(i<2000){
      digitalWrite(relay,LOW);
    }
    else{
  digitalWrite(relay,HIGH);      
    }
  Serial.println(i);
  delay(300);
}