#include <Servo.h>

Servo myServo;
const int trigPin = 9;
const int echoPin = 10;

float duration, distance;

void setup() {
  myServo.attach(6);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  

}

float distanceF() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(100);  

  return distance;

}

void openServo() {

  long distance = distanceF(); 
  Serial.println(distance);

  if (distanceF() < 25) {
    myServo.write(90); 
    delay(1000);
  } else {
    myServo.write(0);
  }

}
hhhhhh
void loop() {
  openServo();
  delay(500);
}
