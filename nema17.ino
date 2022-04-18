#include <Stepper.h>
#define dirPinox 2
#define stepPinox 3
#define dirPinoy 4
#define stepPinoy 5
#define stepsPerRevolution 200

const int stepsPerRevolutionsteppermic = 360;
Stepper myStepper(stepsPerRevolutionsteppermic, 11, 9, 8, 10);

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

void oz()
{
   while(digitalRead(12)==HIGH)
          myStepper.step(stepsPerRevolution);
    while(digitalRead(13)==HIGH)
          myStepper.step(-stepsPerRevolution);
  
}

void loop() {

  oxoy();
  oz();
  
  
}
