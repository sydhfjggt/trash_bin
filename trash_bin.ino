#include <Servo.h>

Servo myServo;
const int trigPin = 9;
const int echoPin = 10;
const int echoPin2 = 11;
const int trigPin2 = 12;


float duration, distance;
float duration2, distance2;

void setup() {
  myServo.attach(6);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  Serial.begin(9600);
}

float distanceF() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration * .0343) / 2;
  Serial.print("Distance: ");
  Serial.println(distance);

  return distance;
}

float distanceL() {
  delay(50);
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = (duration2 * .0343) / 2;
  Serial.print("Distance2: ");
  Serial.println(distance2);

  return distance2;
}

void openServo() {

  float distFront = distanceF();
  float distLeft = distanceL();

 

  if (distFront < 25) {
    myServo.write(90);
  } else if (distLeft < 10) {
    myServo.write(90);
    delay(1000);
  } else {
    myServo.write(0);
  }
}

void loop() {
  openServo();
  delay(500);
}
