#include <Arduino.h>
#include <Servo.h>

Servo myservo;

const int LED_PIN = 13;
const int Trig = 10;
const int Echo = 11;
const int servoPin = 3;
int Duration;
float Distance = 0;


float HC_SR04(){
  float dist;
  digitalWrite(Trig,LOW);
  delayMicroseconds(1);
  digitalWrite(Trig,HIGH);
  delayMicroseconds(11);
  digitalWrite(Trig,LOW);
  Duration = pulseIn(Echo,HIGH);
  if (Duration>20) {
    dist = Duration/2;
    dist = dist*340*100/1000000; // ultrasonic speed is 340m/s = 34000cm/s = 0.034cm/us 
    Serial.print(Duration);
    Serial.print(" us ");
    Serial.print(Distance);
    Serial.println(" cm");
  }else{
    dist = 999;
  }
  return dist;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_PIN,OUTPUT);
  myservo.attach(servoPin);

  pinMode(Trig,OUTPUT);
  pinMode(Echo,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Distance =  HC_SR04();
  if(Distance < 30){
    digitalWrite(LED_PIN,HIGH);
    myservo.write(10);
  }else{
    digitalWrite(LED_PIN,LOW);
    myservo.write(170);
  }
  delay(500);
}

