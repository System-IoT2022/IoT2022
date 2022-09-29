#define BUTTON_PIN 2
int pinA = 13;
int pinB = 12;
int pinC = 11;
int z = 1;
int a = 1;
int c = 0;
int lastState = LOW;
void setup() {
  // put your setup code here, to run once:
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int buttonState = digitalRead(BUTTON_PIN);
  if (buttonState == HIGH && lastState == LOW) {
    delay(15);
    digitalWrite(11 + z, LOW);
    z = (z + a + 3) % 3;
    a = z == 1 ? a : -a;
    digitalWrite(11 + z, HIGH);
    delay(200);
  } else {
    digitalWrite(11 + z, LOW);
  }
  lastState = buttonState;
}