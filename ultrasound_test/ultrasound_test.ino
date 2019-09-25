/*
* Ultrasonic Sensor HC-SR04 and Arduino Tutorial
*
* by Dejan Nedelkovski,
* www.HowToMechatronics.com
*
*/
// defines pins numbers
int ledPin = 13;
const int trigPin = 9;
const int echoPin = 10;
int sensorPin = A0;
int sensorValue = 0;
// defines variables
long duration;
long distance;
void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output  
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin, INPUT);
}
void loop() {
  // Clears the trigPin
  //sensorValue = analogRead(sensorPin);
  //sensorValue = map(sensorValue,0,1023,0,10);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034/2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" . Input : ");
  Serial.println(sensorValue);
  //Serial.println(sensorValue);
  if (distance > 20)
  {
    digitalWrite(ledPin, HIGH);
  }
  else 
  {
     digitalWrite(ledPin, LOW); 
  }
}
