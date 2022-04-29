#include <Stepper.h>
#include <Servo.h>

#define dirPinox 2
#define stepPinox 3
#define dirPinoy 4
#define stepPinoy 5
#define stepsPerRevolution 200

const int stepsPerRevolutionsteppermic = 360;
Stepper myStepper(stepsPerRevolutionsteppermic, 11, 9, 8, 10);
Servo myservo;
int potpin = 4; // pin analog conectare potentiometru
int potpoz= -1;
int _step = 0; 
boolean dir = true;
int Pin0 = 8; 
int Pin1 = 9; 
int Pin2 = 10; 
int Pin3 = 11;

int OX,OY;

void setup() {
  pinMode(stepPinox, OUTPUT);
  pinMode(dirPinox, OUTPUT);
  pinMode(stepPinoy, OUTPUT);
  pinMode(dirPinoy, OUTPUT);
  pinMode(A0,INPUT); ///ox
  pinMode(A1,INPUT);
  myStepper.setSpeed(100);
  Serial.begin(9600);
  pinMode(12,INPUT);
  pinMode(13,INPUT);
  pinMode(9,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  myservo.attach(22);
}

void oxmovement()
{
   for (int i = 0; i < stepsPerRevolution; i++) {
    digitalWrite(stepPinox, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPinox, LOW);
    delayMicroseconds(1000);  }
  
}

void oymovement()
{
   for (int i = 0; i < stepsPerRevolution; i++) {
    digitalWrite(stepPinoy, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPinoy, LOW);
    delayMicroseconds(1000);}
  
}

void oxoy()
{
  OX=analogRead(A0);
  OY=analogRead(A1);

  if(OX<200)
    digitalWrite(dirPinox, HIGH), oxmovement();

  if(OX>800)
    digitalWrite(dirPinox, LOW),oxmovement();

  if(OY<200)
    digitalWrite(dirPinoy, HIGH),oymovement();
   
  if(OY>800)
  digitalWrite(dirPinoy, LOW),oymovement();
}

void clockwise()
{
switch(_step){ 
   case 0: 
     digitalWrite(Pin0, LOW);  
     digitalWrite(Pin1, LOW); 
     digitalWrite(Pin2, LOW); 
     digitalWrite(Pin3, HIGH); 
   break;  
   case 1: 
     digitalWrite(Pin0, LOW);  
     digitalWrite(Pin1, LOW); 
     digitalWrite(Pin2, HIGH); 
     digitalWrite(Pin3, HIGH); 
   break;  
   case 2: 
     digitalWrite(Pin0, LOW);  
     digitalWrite(Pin1, LOW); 
     digitalWrite(Pin2, HIGH); 
     digitalWrite(Pin3, LOW); 
   break;  
   case 3: 
     digitalWrite(Pin0, LOW);  
     digitalWrite(Pin1, HIGH); 
     digitalWrite(Pin2, HIGH); 
     digitalWrite(Pin3, LOW); 
   break;  
   case 4: 
     digitalWrite(Pin0, LOW);  
     digitalWrite(Pin1, HIGH); 
     digitalWrite(Pin2, LOW); 
     digitalWrite(Pin3, LOW); 
   break;  
   case 5: 
     digitalWrite(Pin0, HIGH);  
     digitalWrite(Pin1, HIGH); 
     digitalWrite(Pin2, LOW); 
     digitalWrite(Pin3, LOW); 
   break;  
     case 6: 
     digitalWrite(Pin0, HIGH);  
     digitalWrite(Pin1, LOW); 
     digitalWrite(Pin2, LOW); 
     digitalWrite(Pin3, LOW); 
   break;  
   case 7: 
     digitalWrite(Pin0, HIGH);  
     digitalWrite(Pin1, LOW); 
     digitalWrite(Pin2, LOW); 
     digitalWrite(Pin3, HIGH); 
   break;
   default: 
     digitalWrite(Pin0, LOW);  
     digitalWrite(Pin1, LOW); 
     digitalWrite(Pin2, LOW); 
     digitalWrite(Pin3, LOW); 
   break;  
 }
 if(dir){ 
   _step++; 
 }else{ 
   _step--; 
 } 
 if(_step>7){ 
   _step=0; 
 } 
 if(_step<0){ 
   _step=7; 
 } 
 delay(1); 
}


void counterclockwise ()
{
 switch(_step){
 case 0: 
     digitalWrite(Pin0, HIGH);  
     digitalWrite(Pin1, LOW); 
     digitalWrite(Pin2, LOW); 
     digitalWrite(Pin3, HIGH); 
   break;  
case 1: 
     digitalWrite(Pin0, HIGH);  
     digitalWrite(Pin1, LOW); 
     digitalWrite(Pin2, LOW); 
     digitalWrite(Pin3, LOW); 
   break;   
case 2: 
     digitalWrite(Pin0, HIGH);  
     digitalWrite(Pin1, HIGH); 
     digitalWrite(Pin2, LOW); 
     digitalWrite(Pin3, LOW); 
   break;
case 3: 
     digitalWrite(Pin0, LOW);  
     digitalWrite(Pin1, HIGH); 
     digitalWrite(Pin2, LOW); 
     digitalWrite(Pin3, LOW); 
   break;  
case 4: 
     digitalWrite(Pin0, LOW);  
     digitalWrite(Pin1, HIGH); 
     digitalWrite(Pin2, HIGH); 
     digitalWrite(Pin3, LOW); 
   break;
case 5: 
     digitalWrite(Pin0, LOW);  
     digitalWrite(Pin1, LOW); 
     digitalWrite(Pin2, HIGH); 
     digitalWrite(Pin3, LOW); 
   break; 
case 6: 
     digitalWrite(Pin0, LOW);  
     digitalWrite(Pin1, LOW); 
     digitalWrite(Pin2, HIGH); 
     digitalWrite(Pin3, HIGH); 
   break;
case 7: 
     digitalWrite(Pin0, LOW);  
     digitalWrite(Pin1, LOW); 
     digitalWrite(Pin2, LOW); 
     digitalWrite(Pin3, HIGH); 
   break;
default: 
     digitalWrite(Pin0, LOW);  
     digitalWrite(Pin1, LOW); 
     digitalWrite(Pin2, LOW); 
     digitalWrite(Pin3, LOW); 
   break;   
 }
 if(dir){ 
   _step++; 
 }else{ 
   _step--; 
 } 
 if(_step>7){ 
   _step=0; 
 } 
 if(_step<0){ 
   _step=7; 
 } 
 delay(1); 
}

void oz()
{
   while(digitalRead(12)==HIGH)    
    clockwise();                     
  
   while(digitalRead(13)==HIGH)                              
    counterclockwise(); 

  
}

void claw()
{
  
  potpoz = analogRead(potpin);
  potpoz = map(potpoz, 0, 1023, 29, 65); // scalare in intervalul 0...180
  myservo.write(potpoz); // setare pozitie servo
  delay(15); // asteptare rotire servo

  
}

void loop() {
  
  oxoy();
  oz();
  if(analogRead(potpin)!=potpoz)
      claw();
  
  
}
