#include<SimpleTimer.h>
SimpleTimer timer;

int echoPin = 37;
int trigPin = 38;
float duration, distance;

void setup(){
  Serial.begin(115200); Serial1.begin(115200);
  
  timer.setInterval(100,Uart1); 
  timer.setInterval(100,wave); 
  
  pinMode(4, OUTPUT); pinMode(5, OUTPUT); 
  pinMode(28, OUTPUT); pinMode(29, OUTPUT);
  pinMode(30, OUTPUT); pinMode(31, OUTPUT); 
  pinMode(trigPin, OUTPUT); pinMode(echoPin, INPUT); 
  pinMode(17, OUTPUT); 

}

unsigned char Uart0ProtocolPointer = 0;
unsigned char Uart0ReciveCheckEnd = 0;
unsigned char Data[12]={0,};
unsigned int X_center=0;
unsigned int Y_center=0;
unsigned int prev=0;
unsigned int cur=0;
int flag;
int endline = 255;

void UartRxProtocol(){
  unsigned char Uart0_Data;
  if(Serial.available()){ 
      Uart0_Data = Serial.read();         
      
      switch(Uart0ProtocolPointer){ 
        case 0: if(0xaa == Uart0_Data){Uart0ProtocolPointer =1;} 
                else{ Uart0ProtocolPointer =0;} break;
        case 1: if(0x55 == Uart0_Data){Uart0ProtocolPointer =10;}
                else{Uart0ProtocolPointer =0;} break;
        case 10: Data[0] = Uart0_Data; Uart0ProtocolPointer =11; break;
        case 11: Data[1] = Uart0_Data; Uart0ProtocolPointer =12; break;
        case 12: Data[2] = Uart0_Data; Uart0ProtocolPointer =13; break;
        case 13: Data[3] = Uart0_Data; Uart0ProtocolPointer =14; break;
        case 14: Data[4] = Uart0_Data; Uart0ProtocolPointer =15; break;
        case 15: Data[5] = Uart0_Data; Uart0ProtocolPointer =16; break;//x
        case 16: Data[6] = Uart0_Data; Uart0ProtocolPointer =17; break;
        case 17: Data[7] = Uart0_Data; Uart0ProtocolPointer =18; break;//y
        case 18: Data[8] = Uart0_Data; Uart0ProtocolPointer =19; break;
        case 19: Data[9] = Uart0_Data; Uart0ProtocolPointer =20; break;
        case 20: Data[10] = Uart0_Data; Uart0ProtocolPointer =21; break;
        case 21: Data[11] = Uart0_Data; Uart0ProtocolPointer =100; break;

        case 100: if(0x00 == Uart0_Data){Uart0ProtocolPointer =101;}
                  else {Uart0ProtocolPointer =0;} break;
        case 101: if(0x00 == Uart0_Data){Uart0ProtocolPointer =102;}
                  else {Uart0ProtocolPointer =0;} break;
        case 102: if(0x00 == Uart0_Data){Uart0ProtocolPointer =103;}
                  else {Uart0ProtocolPointer =0;} break;
        case 103: if(0x55 == Uart0_Data){Uart0ProtocolPointer =0; Uart0ReciveCheckEnd=1;}
                  else {Uart0ProtocolPointer =0;} break; 
        default: Uart0ProtocolPointer = 0; break;        
      }
  }
}

void Serial_Main0(void){
  if(Uart0ReciveCheckEnd==1){ 
    Uart0ReciveCheckEnd =0;
    prev = X_center; //이전
    
    //new
    X_center = Data[5]; 
    Y_center = Data[7];

    unsigned int color = Data[3]; // 1노랑(공) 2초록(골대)
    Serial1.print("color: ");
    Serial1.println(color);
    
    //overflow 
    if(prev > 200 && X_center < 100 || cur > 200 && X_center < 100) cur = (X_center + endline);      
    else cur =  X_center; 

    //15cm 이하면 초음파 이상이면 픽시? 
    
    //모터제어
    //0은 정지 , 1은 직진 , 2는 우회전 , 3은 좌회전   



   if(color == 1){        
        if (cur <= 50) {  //좌       
          analogWrite(4, 42); digitalWrite(28, LOW); digitalWrite(29, HIGH);
          analogWrite(5, 50); digitalWrite(30, LOW); digitalWrite(31, HIGH);
        }else if (cur > 50 && cur < 194) {
          analogWrite(4, 50); digitalWrite(28, LOW); digitalWrite(29, HIGH);
          analogWrite(5, 50); digitalWrite(30, HIGH); digitalWrite(31, HIGH);
        }else if (cur >= 194) { //우
          analogWrite(4, 50); digitalWrite(28, HIGH); digitalWrite(29, HIGH);
          analogWrite(5, 42); digitalWrite(30, HIGH); digitalWrite(31, HIGH);
        }else if(cur == 0){
          analogWrite(4, 10); digitalWrite(28, HIGH); digitalWrite(29, HIGH);
          analogWrite(5, 10); digitalWrite(30, HIGH); digitalWrite(31, HIGH);
        }
      }else if(color == 2 || color == 3 || color == 2 ){            
          if (cur <= 50) {  //좌       
            analogWrite(4, 50); digitalWrite(28, LOW); digitalWrite(29, HIGH);
            analogWrite(5, 50); digitalWrite(30, LOW); digitalWrite(31, HIGH);
          }else if (cur > 50 && cur < 194) {
            analogWrite(4, 50); digitalWrite(28, LOW); digitalWrite(29, HIGH);
            analogWrite(5, 50); digitalWrite(30, HIGH); digitalWrite(31, HIGH);
          }else if (cur >= 194) { //우           
            analogWrite(4, 50); digitalWrite(28, HIGH); digitalWrite(29, HIGH);
            analogWrite(5, 50); digitalWrite(30, HIGH); digitalWrite(31, HIGH);
          }    
        } else //직진
        {
            analogWrite(4, 50); digitalWrite(28, LOW); digitalWrite(29, HIGH);
            analogWrite(5, 50); digitalWrite(30, HIGH); digitalWrite(31, HIGH);

        }           
      }     
}

void Uart1(){  
  Serial1.print(X_center);
  Serial1.print(' ');
  Serial1.println(Y_center);
}


void wave(){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034/2;
    Serial1.println(duration);
    
    Serial1.print(distance);
    Serial1.println("cm");
    delay(5);
}



void loop(){
  timer.run(); 
  UartRxProtocol();
  Serial_Main0();
  }
