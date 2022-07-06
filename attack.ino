#include <SimpleTimer.h> 
SimpleTimer timer; 
boolean On=false;
 

void setup() { 
  //PORTE
  pinMode(4, OUTPUT); pinMode(5, OUTPUT); 
  //PORTC
  pinMode(28, OUTPUT); pinMode(29, OUTPUT);
  pinMode(30, OUTPUT); pinMode(31, OUTPUT); 

  timer.setInterval(400,toggle);
}


int count=0;
void toggle(){
    if(count>=2){
      On=true;
    }
    if(On==false){
      analogWrite(4,1000); digitalWrite(28,LOW);digitalWrite(29,HIGH);
      analogWrite(5,1000); digitalWrite(30,HIGH);digitalWrite(31,HIGH);
    }
    else{
           analogWrite(4,0); digitalWrite(28,HIGH);digitalWrite(29,HIGH);
           analogWrite(5,0); digitalWrite(30,LOW);digitalWrite(31,HIGH);
    }
    On =! On;
    count++;  
}


void loop() { 
      timer.run();
//     if(Rx_data==0x31){ //직진
//        analogWrite(4,40); digitalWrite(28,LOW);digitalWrite(29,HIGH);
//        analogWrite(5,40); digitalWrite(30,HIGH);digitalWrite(31,HIGH);
//      }
//      else if(Rx_data==0x32){
//        analogWrite(4,30); digitalWrite(28,HIGH);digitalWrite(29,HIGH);
//        analogWrite(5,30); digitalWrite(30,HIGH);digitalWrite(31,HIGH);
//      }
//      else if(Rx_data==0x33){ //좌회전
//        analogWrite(4,20); digitalWrite(28,LOW);digitalWrite(29,HIGH);
//        analogWrite(5,20); digitalWrite(30,LOW);digitalWrite(31,HIGH);
//      }
//      else if(Rx_data==0x34){ //후진.
//        analogWrite(4,40); digitalWrite(28,HIGH);digitalWrite(29,HIGH);
//        analogWrite(5,40); digitalWrite(30,LOW);digitalWrite(31,HIGH);
//      }
//      else if(Rx_data==0x30){
//        analogWrite(4,0); digitalWrite(28,HIGH);digitalWrite(29,LOW);
//        analogWrite(5,0); digitalWrite(30,HIGH);digitalWrite(31,LOW);
//      }
  
}
