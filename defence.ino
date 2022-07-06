#include<SimpleTimer.h>
SimpleTimer timer;

int echoPin = 37;
int trigPin = 38;
float duration, distance;

void setup(){
  Serial.begin(115200); Serial1.begin(115200); 
  pinMode(4, OUTPUT); pinMode(5, OUTPUT); 
  pinMode(28, OUTPUT); pinMode(29, OUTPUT);
  pinMode(30, OUTPUT); pinMode(31, OUTPUT); 
  pinMode(trigPin, OUTPUT); pinMode(echoPin, INPUT); 
  pinMode(17, OUTPUT); 

}



void loop(){
  timer.run(); 


   analogWrite(4,50); digitalWrite(28,LOW);digitalWrite(29,HIGH); 
   analogWrite(5,50); digitalWrite(30,LOW);digitalWrite(31,HIGH);
}
