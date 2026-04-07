void setup() {
 DDRD |= B11111111;
}
void loop() {
PORTD = B00000011;
delay (50);
 for(int i=0;i<=4;i++){
 PORTD = PORTD<<2;
 delay(50);
 }
 PORTD = B11000000;
delay (50);
 for(int i=0;i<=4;i++){
 PORTD = PORTD>>2;
 delay(50);
 }
}
