// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>
#include <Servo.h>
#include <math.h>

// other variables
int localDistance;
// Pin variables
const int in_1 = 5;
const int out_1 = 6;
const int out_2 = 9;
const int in_2 = 3;
const int ena = 13;
const int enb = 12;
const int echoPin1 = 10;
const int pingPin1 = 7;
const int echoPin2 = 4;
const int pingPin2 = 2;
static long duration, distance, duration2, distance2, predistance, predistance2;
// the array to store the currently calculated differences in distances
double values[3];
// pointer to access the array and change the values
double *p;
const int leftwheelspeed = 255;
const int rightwheelspeed = 250;
// 27/02/2019
// DC hobby serv

void setup(){

  p = &values[0];
  pinMode(echoPin1, INPUT);
  pinMode(pingPin1, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(pingPin2, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A5, INPUT);   
  pinMode(in_1,OUTPUT);
  pinMode(out_1,OUTPUT);
  pinMode(out_2,OUTPUT);
  pinMode(in_2,OUTPUT);
  pinMode(ena,OUTPUT);
  pinMode(enb,OUTPUT);
  
  digitalWrite(ena,HIGH);
  digitalWrite(enb,HIGH);
  // right wheels
  analogWrite(in_1,leftwheelspeed);
  analogWrite(out_1,0);
  // left wheels
  analogWrite(out_2,0);
  analogWrite(in_2,rightwheelspeed);
  Serial.begin(9600);
  
}


// Test the DC motor, stepper and servo ALL AT ONCE!
void loop() {

  // sensing the distance
  pingboth(pingPin1, echoPin1, pingPin2, echoPin2);
  Serial.print("Difference right sensor : ");
  Serial.print(values[0]);
  Serial.print("  ");
  Serial.print("Front sensor value : ");
  Serial.println(values[1]);
  // values[1] = front sensor distance
  // values[0] change in distance 
  moveForward();
  delay(50);
 
}
long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}

/* returns the array values to be stored in an array in main 
   by pinging both sensors forward and right and calculating 
   the difference between each sensor reading and the last reading
   the sensor made*/
void pingboth(int trigPin, int echoPin , int trig2Pin, int echo2Pin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(1);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  distance= duration*0.034/2;

  
  digitalWrite(trig2Pin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trig2Pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2Pin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration2 = pulseIn(echo2Pin, HIGH);
  
  // Calculating the distance
  distance2= duration2*0.034/2;
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance right: ");
  Serial.print(distance);
  Serial.print("  | ");
  Serial.print("Distance forward: ");
  Serial.println(distance2);
  Serial.print("pDistance right: ");
  Serial.print(predistance);
  Serial.print("  | ");
  Serial.print("pDistance forward: ");
  Serial.println(predistance2);
  // calculate the vales of the array and change the pointer
  *p = distance - predistance;
  p = &values[1];
  *p = abs(distance2);
  p = &values[2];
  *p = distance;
  p = &values[0];
  predistance = distance;
  predistance2 = distance2;
}

void resetSensor(){
  distance = predistance;
  distance2 = predistance2;
}


void moveForward () {
  analogWrite(in_1,leftwheelspeed);
  analogWrite(out_1,0);
  // left wheels
  analogWrite(out_2,0);
  analogWrite(in_2,rightwheelspeed);
}

void stopMotors(){
  analogWrite(out_1,0);
  analogWrite(in_1,0);
  analogWrite(out_2,0);
  analogWrite(in_2,0);
}
