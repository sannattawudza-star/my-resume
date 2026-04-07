#define led1 15
#define led2 0
#define led3 4
#define led4 16
#define led5 13
#define led6 14
#define led7 27
#define led8 26
int led;
void setup() {
  int i[]={15,0,4,16,13,14,27,26};
  for(led=0;led<=8;led++)
  {
    pinMode(led[i],OUTPUT);
    digitalWrite(led[i],1);
  }
}
void loop() { 
  digitalWrite(led7,1);
  digitalWrite(led8,1);  
  digitalWrite(led1,0);
  digitalWrite(led2,0);
  delay(500);
  digitalWrite(led1,1);
  digitalWrite(led2,1);
  digitalWrite(led3,0);
  digitalWrite(led4,0);  
  delay(500);
  digitalWrite(led1,1);
  digitalWrite(led2,1);
  digitalWrite(led3,1);
  digitalWrite(led4,1); 
  digitalWrite(led5,0);
  digitalWrite(led6,0);  
  delay(500);
  digitalWrite(led1,1);
  digitalWrite(led2,1);
  digitalWrite(led3,1);
  digitalWrite(led4,1); 
  digitalWrite(led5,1);
  digitalWrite(led6,1); 
  digitalWrite(led7,0);
  digitalWrite(led8,0);  
  delay(500);
}
