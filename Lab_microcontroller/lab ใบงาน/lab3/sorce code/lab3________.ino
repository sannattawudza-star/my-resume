#define led 13
#define sw1 12
#define sw2 11
#define D0 10
#define D1 9
#define D2 5
#define D3 7
#define D4 6
int i,;
void setup()  {
  pinMode(D0, INPUT);  
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);  
  pinMode(D3, INPUT);
  pinMode(D4, INPUT);  
  pinMode(sw1,INPUT);  
  pinMode(sw2,INPUT);
  pinMode(led,OUTPUT);
  Serial.begin(9600);
  Serial.println("Choose GATE ");
  Serial.println("1. AND GATE ");
  Serial.println("2. OR GATE ");
  Serial.println("2. NOT GATE ");
  Serial.println("4. NOR GATE ");
  Serial.println("5. NAND GATE ");
  int sw11=digitalRead(sw1);
  int sw22=digitalRead(sw2);
    for(i=0;i<1;i){
    if (digitalRead(D0)==1){
      Serial.println("Choose AND gate");
     i=1;       
    }
    else if(digitalRead(D1)==1){
      Serial.println("Choose OR gate");
      i=2;
    }
    else if(digitalRead(D2)==1){
      Serial.println("Choose NOT gate");
      i=3;
    }
    else if(digitalRead(D3)==1){
      Serial.println("Choose NOR gate");      
      i=4;
    }
    else if(digitalRead(D4)==1){
      Serial.println("Choose NAND gate");    
      i=5;
    }
    }
     if(i == 1){  // การทำงานของ AND gate
      if(sw11 == 1 && sw22 == 1){
        Serial.println("OUTPUT = 1");
        digitalWrite(led,1);
      }
      else{
        Serial.println("OUTPUT = 0");
        digitalWrite(led,0);
      }
    }
    if(i == 2){ //การทำงานของ OR gate
      if(sw11 == 0 && sw22 == 0 ){
        Serial.println("OUTPUT is 0");
        digitalWrite(led,0);
      }
      else{
        Serial.println("OUTPUT = 1");
        digitalWrite(led,1);
      }
    }
        if(i == 3){ //การทำงานของ NOT gate
      if(sw11 == 0 || sw22 == 0 ){
        Serial.println("OUTPUT is 1");
        digitalWrite(led,1);
      }
      else{
        Serial.println("OUTPUT = 0");
        digitalWrite(led,0);
      }
        }
          if(i == 4){   // การทำงานของ NOR gate
      if(sw11 == 0 && sw22 == 0 ){
        Serial.println("OUTPUT is 1");
        digitalWrite(led,1);
      }
      else{
        Serial.println("OUTPUT = 0");
        digitalWrite(led,0);
      }
          }
          if(i == 5){   //การทำงานของ NAND gate
      if(sw11 == 1 && sw22 == 1 ){
        Serial.println("OUTPUT is 0");
        digitalWrite(led,0);
      }
      else{
        Serial.println("OUTPUT = 1");
        digitalWrite(led,1);
          }
      }
}
void loop() {
    
}
