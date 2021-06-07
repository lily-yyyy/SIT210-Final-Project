#include <math.h>

const int trigPin = D7;
const int echoPin = D2;


const float eyescreen = 50;

float duration, distance;

bool debOperator = false;


void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  pinMode(ledRPin, OUTPUT);
  pinMode(ledGPin, OUTPUT);
  pinMode(ledBPin, OUTPUT);
  
  Serial.begin(9600);
}

float getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  return (distance);
}


void loop(){
  distance = getDistance();
  Serial.print("Distance: ");
  Serial.println(distance);
  
  
  bool verifier = (distance <= eyescreen);
  if (verifier){
      if (debOperator){
        Serial.println("Don't be that close to the screen.");
      Particle.publish("verifier", "true", PRIVATE);  
      debOperator = false;
      }
  }
  else {
      debOperator = true;
  }
  delay(100);
}