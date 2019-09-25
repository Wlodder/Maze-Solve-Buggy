int motorPin1 = 2;
int motorPin2 = 3;

int motor1Speed = 255;
int motor2Speed = 255;


void setup() {
   analogWrite(motorPin1, 255); analogWrite(motorPin2, 255);
   delay(10000);
   analogWrite(motorPin1, 0); analogWrite(motorPin2, 0);
   delay(10000);
}
void loop() {
  analogWrite(motorPin1, motor1Speed);
  analogWrite(motorPin2, motor2Speed);
  delay(2);
}
