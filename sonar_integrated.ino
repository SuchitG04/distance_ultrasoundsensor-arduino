#include <SevSeg.h>

SevSeg sevseg; // Instantiate a seven segment display object

// Defines Trig and Echo pins of the Ultrasonic Sensor
const int trigPin = 14;
const int echoPin = 15;
const int greenLed = 3;

// Variables for the duration and the distance
long duration;
int distance;

void setup() {
  byte numDigits = 4;
  byte digitPins[] = {5, 4, 2, 1};
  byte segmentPins[] = {13, 12, 11, 10, 9, 8, 7, 6};
  bool resistorsOnSegments = true;
  byte hardwareConfig = COMMON_ANODE;
  bool updateWithDelays = false;
  bool leadingZeros = false;
  bool disableDecPoint = false;

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(90);
  
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(greenLed, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  delay(5);
    
  distance = calculateDistance();// Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
  int intensity = 255 - (int)distance * 2.5;
  if (intensity <= 0)
  {
    analogWrite(greenLed, 0);
  }
  else
  {
    analogWrite(greenLed, intensity);
  }

  sevseg.setNumber(distance);
  sevseg.refreshDisplay();

  Serial.print(distance); // Sends the distance value into the Serial Port
  Serial.print("\t");
}
  
// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance(){ 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance = duration*0.034/2;
  return distance;
}
