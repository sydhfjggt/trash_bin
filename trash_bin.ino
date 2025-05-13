/* File: trash_bin
Author: Julius Markensten
Date: 2025-05-13
Description: This program uses HC-SR04 and a servomotor to allow open a trash can automatically. 
The HC-SR04 measures the distance both outside the box and inside the box and then the servomotor turn 90 degrees if the distance is close enough. It opens if you are close enough outside or if the trash can is full enough.
*/

/*
Includes the librarie for the servomotor*/
#include <Servo.h>

Servo myServo; // create Servo object to control the servo
/*Initializes constants for trigpin and echopin*/
const int trigPin = 9;
const int echoPin = 10;
const int echoPin2 = 11;
const int trigPin2 = 12;

/*Initializes constants duration and distance in float allowing them to be measures in decimals */
float duration, distance;
float duration2, distance2;


void setup() {
  myServo.attach(6);
  // Set trigpin as output and echopin as input 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  // Correct rate for sensors
  Serial.begin(9600);
}

float distanceF() { // This function measures the distence on one HC-SR04
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH); // The sensor measures by soundwaves so it measures the time it takes for the soundwave to bounce back and return duration
  distance = (duration * .0343) / 2; // The distance is measured from the duration and converted to cm
  Serial.print("Distance: ");
  Serial.println(distance);

  return distance;
}

float distanceL() { // This function measures the distence on one HC-SR04
  delay(50);
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  duration2 = pulseIn(echoPin2, HIGH); // The sensor measures by soundwaves so it measures the time it takes for the soundwave to bounce back and return duration
  distance2 = (duration2 * .0343) / 2; // The distance is measured from the duration and converted to cm
  Serial.print("Distance2: ");
  Serial.println(distance2);

  return distance2;
}

void openServo() {

  /*Assign results from distanceF and L to float variables distFront and distLeft*/
  float distFront = distanceF(); 
  float distLeft = distanceL();

  /*If distance is less than x cm the servo turns 90 degrees*/
  if (distFront < 25) { // For the sensor outside the trash can
    myServo.write(90);
  } else if (distLeft < 10) { // For the sensor inside the trash can
    myServo.write(90);
    delay(1000);
  } else {
    myServo.write(180); // If the distance is more than both it stays 180 degrees
  }
}

void loop() { // Function to allow the servo to turn
  openServo();
  delay(500);
}