turning a motor off/on delay period of and light on and off

int motorPin = 9;
int LED = 13;
void setup() {
     pinMode(motorPin, OUTPUT);
     pinMode(LED, OUTPUT);
}
void loop() {
     digitalWrite(motorPin, HIGH);
     digitalWrite(LED, LOW);
     delay(1000);
     digitalWrite(motorPin, LOW);
     digitalWrite(LED, HIGH);
     delay(1000);
}
