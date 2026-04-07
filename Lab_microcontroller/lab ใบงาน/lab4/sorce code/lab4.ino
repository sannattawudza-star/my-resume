void setup()  {
  DDRD |= B11111111;
}
void loop() {
PORTD = B00000001;
delay (250);
  for(int i=0;i<=7;i++){
    PORTD = PORTD<<1;
    delay(250);
   }
}
