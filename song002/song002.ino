int pinA = 13;
int pinB=12;
int pinC=11;
int z=0;
int a=1;
void setup() {
  // put your setup code here, to run once:
  pinMode(pinA,OUTPUT);
  pinMode(pinB,OUTPUT);
  pinMode(pinC,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite( 3 * (abs(sin(z))+1) + 10,LOW);  
  z += 90;
  digitalWrite( 3 * (abs(sin(z))+1) + 10,HIGH);  
  delay(500);
  //digitalWrite( 3 * abs(sin(z)) + 11,LOW);  
}
