int i[]={15,0,4,16,13,14,27,26};
int led;
void setup() {
  for( led=0;led<=7;led++)
  {
    pinMode(led[i],OUTPUT);
  }
 }
void loop() {
        for(led=0;led<=7;led++)
        {
          digitalWrite(led[i],0);
          delay(250);
        }
        for(led=1;led<=7;led++)
        {
          digitalWrite(led[i],1);
          delay(250);
        }
      }
