#define sw1 17
#define sw2 4
#define led1 16
int sw11,sw22;
void setup() {
  Serial.begin(115200);
  pinMode(sw1,INPUT);
  pinMode(sw2,INPUT);
  pinMode(led1,OUTPUT); 
}

void loop() {
   sw11=digitalRead(sw1);
   sw22=digitalRead(sw2);
 Serial.println(sw11);
 Serial.println(sw22);
 if(sw11 != sw22){
  digitalWrite(led1,LOW);
 }
 else{
  digitalWrite(led1,HIGH);
 }
}
