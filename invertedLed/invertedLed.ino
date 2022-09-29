int pinA = 13;
int pinB=12;
int pinC=11;
int z=1;
int a=1;
void setup() {
  // put your setup code here, to run once:
  pinMode(pinA,OUTPUT);
  pinMode(pinB,OUTPUT);
  pinMode(pinC,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(11+z,LOW);  
  z=(z+a+3)%3;
  a=z==1?a:-a;
  digitalWrite(11+z,HIGH);    
  delay(500);
}
