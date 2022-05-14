#include <Stepper.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

#define dirPinox 2 ///nema17
#define stepPinox 3
#define dirPinoy 4
#define stepPinoy 5
#define stepsPerRevolution 200
#define SS_PIN 53
#define RST_PIN 46

LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 mfrc522(SS_PIN, RST_PIN);

const int stepsPerRevolutionsteppermic = 360;
Stepper myStepper(stepsPerRevolutionsteppermic, 11, 9, 8, 10);
Servo myservo;

int pag=1; //pagina pt lcd 
int pressed=0; //pt lcd
int credit=0,time=0,start=0;
int potpoz= -1;
int _step = 0; 
boolean dir = true;
int OX,OY;
long timp = 120; //start time 
int x = 1000; 
int del = 55; //delay value
int cif=1;
int sen1=3, sen2=4, sen3=5, sen4=6;//pini analogi senzori
int valn1=0, valn2=0, valn3=0, valn4=0;
int led=35;
int deridicat=0;
int obiectecastigate=0;
double ozpozitie=0;
double oxpozitie=0;
double oypozitie=0;

int potpin =2; // pin analog conectare potentiometru
int Pin0 = 8; //pini pt stepper5v sus-jos
int Pin1 = 9; 
int Pin2 = 10; 
int Pin3 = 11;
long long timptrecut=millis();

const int a = 40;
const int b = 41;
const int c = 38;
const int d = 39;
const int e = 36;
const int f = 37;
const int g = 34;
const int d4 =45;
const int d3 =44;
const int d2 =43;
const int d1 =42;

byte t[8] =   
{
0b01000,
0b11100,
0b01000,
0b01000,
0b01001,
0b00110,
0b00000,
0b00100
};

byte a1[8] =
{
0b01010,
0b00100,
0b00000,
0b01110,
0b00001,
0b01111,
0b10001,
0b01111
};

byte a2[8] =  
{
0b00100,
0b01010,
0b00000,
0b01110,
0b00001,
0b01111,
0b10001,
0b01111
};

byte i[8] = 
{
0b00100,
0b01010,
0b00000,
0b01100,
0b00100,
0b00100,
0b01110,
0b00000
};

void setup() {
  Serial.begin(9600);
  myStepper.setSpeed(100);
  myservo.attach(22);
  SPI.begin(); // Initiate SPI bus
  mfrc522.PCD_Init(); // Initiate MFRC522
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d4, OUTPUT);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(35,OUTPUT);

  pinMode(6,INPUT);
  pinMode(7,INPUT);
  pinMode(12,INPUT);
  pinMode(13,INPUT);
  pinMode(19,INPUT);

  pinMode(9,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);

  pinMode(stepPinox, OUTPUT);
  pinMode(dirPinox, OUTPUT);
  pinMode(stepPinoy, OUTPUT);
  pinMode(dirPinoy, OUTPUT);

  pinMode(A0,INPUT); ///ox
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  
  lcd.init(); // initialize the lcd
  lcd.backlight();
  lcd.createChar(3,t);
  lcd.createChar(4,a2);
  lcd.createChar(5,i);
  lcd.createChar(7,a1);
}

//LCD
void sageatadr()
{
  lcd.setCursor(15,1);
  lcd.write((char) 126);
}

void sageatast()
{
  lcd.setCursor(0,1);
  lcd.write((char) 127);
}

void paganimatie0(){
  lcd.clear();
  lcd.setCursor(2,0);        
  lcd.print("Introdu");
  lcd.setCursor(3,1);        
  lcd.print("Credit!");
  lcd.setCursor(11,1);
  lcd.write((char)40);
  lcd.setCursor(15,1);
  lcd.write((char)41);
  lcd.setCursor(13,0);
  lcd.print("_");
  lcd.setCursor(12,0);
  lcd.print("A");
  lcd.setCursor(14,0);
  lcd.print("A");
  lcd.setCursor(13,1);
  lcd.write((char)169);
  lcd.setCursor(12,1);
  lcd.write((char)111);
  lcd.setCursor(14,1);
  lcd.write((char)111);
  
  
}

void paganimatie1(){

  lcd.clear();
  lcd.setCursor(3,0);        
  lcd.print("Introdu");
  lcd.setCursor(2,1);        
  lcd.print("Credit!");
  lcd.setCursor(11,1);
  lcd.write((char)40);
  lcd.setCursor(15,1);
  lcd.write((char)41);
  lcd.setCursor(13,0);
  lcd.print("_");
  lcd.setCursor(12,0);
  lcd.print("n");
  lcd.setCursor(14,0);
  lcd.print("n");
  lcd.setCursor(13,1);
  lcd.write((char)169);
  lcd.setCursor(12,1);
  lcd.write((char)62);
  lcd.setCursor(14,1);
  lcd.write((char)60);
  
}

void animatie0(){
  lcd.setCursor(5,1);
  lcd.write((char)161);
  lcd.setCursor(6,1);
  lcd.write((char)223);
  lcd.setCursor(7,1);
  lcd.write((char)161);
  lcd.setCursor(8,1);
  lcd.write((char)223);
  lcd.setCursor(9,1);
  lcd.write((char)161);
  lcd.setCursor(10,1);
  lcd.write((char)223);
  lcd.setCursor(11,1);
  lcd.write((char)161);
  
  
}

void animatie1(){
  lcd.setCursor(5,1);
  lcd.write((char)223);
  lcd.setCursor(6,1);
  lcd.write((char)161);
  lcd.setCursor(7,1);
  lcd.write((char)223);
  lcd.setCursor(8,1);
  lcd.write((char)161);
  lcd.setCursor(9,1);
  lcd.write((char)223);
  lcd.setCursor(10,1);
  lcd.write((char)161);
  lcd.setCursor(11,1);
  lcd.write((char)223);
}

void pag1(){

  lcd.clear();
  lcd.setCursor(2,0);        
  lcd.print("Instructiuni:");
  lcd.setCursor(9,0);
  lcd.write(byte(3)); 
  sageatadr();

  /*while(digitalRead(6)==LOW && digitalRead(7)==LOW)
  {
    animatie0();
    delay(400);
    animatie1();
    delay(400);
  }*/
}

void pag2(){

  lcd.clear();
  lcd.setCursor(1,0);        
  lcd.print("Prinde cat mai");
  lcd.setCursor(9,0);
  lcd.write(byte(4));
  lcd.setCursor(5,1);
  lcd.print("multe");     
  sageatast();
  sageatadr();
}

void pag3(){

  lcd.clear();
  lcd.setCursor(0,0);        
  lcd.print("Obiecte intr-un");
  lcd.setCursor(8,0);
  lcd.write(byte(5));
  lcd.setCursor(5,1);
  lcd.print("minut!");     
  sageatast();
  sageatadr();
}

void pag4(){
  
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Potentiometrul");
  lcd.setCursor(6,0);
  lcd.write(byte(3));
  lcd.setCursor(4,1);
  lcd.print("inchide");
  lcd.setCursor(4,1);
  lcd.write(byte(5));
  sageatast();
  sageatadr();
}

void pag5(){
  
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("Si deschide");
  lcd.setCursor(5,1);
  lcd.print("gheara");
  sageatast();
  sageatadr();
}

void pag6(){
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Pentru a incepe");
  lcd.setCursor(9,0);
  lcd.write(byte(5));
  lcd.setCursor(2,1);
  lcd.print("apasa start!");
  lcd.setCursor(6,1);
  lcd.write(byte(7));
  
  sageatast();
  sageatadr();

}

void pag7(){
  
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("Succes!");
  sageatast();


}

void pagfelicitari(){
 
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("FELICITARI!");
  lcd.setCursor(4,1);
  lcd.print("+1 obiecte");

}

void mesajfinal(){

  lcd.clear();

  if(obiectecastigate>0){
  lcd.setCursor(3,0);
  lcd.print("Ai castigat");
  lcd.setCursor(3,1);
  lcd.print(obiectecastigate);
  lcd.setCursor(5,1);
  lcd.print("obiecte!");
  }

  if(obiectecastigate==0){
    
  lcd.setCursor(0,0);
  lcd.print("Nu ai castigat obiecte");
  lcd.setCursor(0,1);
  lcd.print("Mai incearca!");
  }


  delay(9000);
}

void switcher(){

   switch(pag)
   {
    case 1: 
    pag1();
    break;

    case 2: 
    pag2();
    break;

    case 3: 
    pag3();
    break;

    case 4: 
    pag4();
    break;

    case 5: 
    pag5();
    break;

    case 6: 
    pag6();
    break;

    case 7: 
    pag7();
    break;


   }
}

//Timer
void timer(){   

  clearLEDs();
  pickDigit(1);
  pickNumber((timp/1000)%10);
  delayMicroseconds(10000);

  clearLEDs();
  pickDigit(2);
  pickNumber((timp/60)%10);
  delayMicroseconds(10000);
 
  clearLEDs();
  pickDigit(3);
  pickNumber((timp/10)%6);
  delayMicroseconds(10000);

  clearLEDs();
  pickDigit(4);
  pickNumber(timp%10);
  delayMicroseconds(10000);

}

void pickDigit(int x)
{
  digitalWrite(d1, HIGH);
  digitalWrite(d2, HIGH);
  digitalWrite(d3, HIGH);
  digitalWrite(d4, HIGH);

  switch(x)
  {
  case 1: 
    digitalWrite(d1, LOW); 
    break;
  case 2: 
    digitalWrite(d2, LOW); 
    break;
  case 3: 
    digitalWrite(d3, LOW);
    break;
  case 4: 
    digitalWrite(d4, LOW); 
    break;
  }
}
 
void pickNumber(int x) 
{
  switch(x)
  {
  default: 
    zero(); 
    break;
  case 1: 
    one(); 
    break;
  case 2: 
    two(); 
    break;
  case 3: 
    three(); 
    break;
  case 4: 
    four(); 
    break;
  case 5: 
    five(); 
    break;
  case 6: 
    six(); 
    break;
  case 7: 
    seven(); 
    break;
  case 8: 
    eight(); 
    break;
  case 9: 
    nine(); 
    break;
  }
}

void clearLEDs()
{
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}
 
void zero()
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
}
 
void one()
{
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}
 
void two()
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
}
 
void three()
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
}
 
void four()
{
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}
 
void five()
{
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}
 
void six()
{
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}
 
void seven()
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}
 
void eight()
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}
 
void nine()
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

//Senzori cadere
void ajustaresenzorisimediesenzori(){
  valn1=0;
  valn2=0;
  valn3=0;
  valn4=0;
  for(int i=1;i<=5;i++){
    delay(100);
    valn1=valn1+analogRead(sen1);
    valn2=valn2+analogRead(sen2);
    valn3=valn3+analogRead(sen3);
    valn4=valn4+analogRead(sen4);
  }
  valn1=valn1/5;
  valn2=valn2/5;
  valn3=valn3/5;
  valn4=valn4/5;
   delay(50);
}

int cadere(){

  if(analogRead(sen1)+60<=valn1)
    return 1;

  if(analogRead(sen2)+60<=valn2)
    return 1;

  if(analogRead(sen3)+60<=valn3)
    return 1;
  
  if(analogRead(sen4)+50<=valn4)
    return 1;
  
   return 0;
}

//Buzzer
/*
void canteccadere(){
}

void cantecfinal(){  ///cantec cand se afiseaza scorul final
}

void cantecinceput(){
}*/

//X Y Z
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
   while(digitalRead(7)==HIGH){    //injos  
    
     if(ozpozitie>4500)
        ozpozitie=4510;
        
     if(ozpozitie<=4500)
        clockwise(),ozpozitie=ozpozitie+0.25;          
    }          
  
   while(digitalRead(6)==HIGH){ 

      if(ozpozitie<-3000)
        ozpozitie=-3010;
    
     if(ozpozitie>=-3000)
       counterclockwise(),ozpozitie=ozpozitie-0.25;
}
}

void repozitionareoz(){
   
   while(!(ozpozitie>=-1 && ozpozitie<=1)){
   if(ozpozitie>0)
        counterclockwise(),ozpozitie=ozpozitie-0.25;

   if(ozpozitie<0)
         clockwise(),ozpozitie=ozpozitie+0.25;
}
}

void claw()
{
  
  potpoz = analogRead(potpin);
  potpoz = map(potpoz, 0, 1023, 29, 65); // scalare in intervalul 0...180
  myservo.write(potpoz); // setare pozitie servo
  delay(10); // asteptare rotire servo

  
}


void loop() {

  if(mfrc522.PICC_IsNewCardPresent() && credit==0 && start==0)       
       credit=1, digitalWrite(35,HIGH), pag1();//cantecinceput();
  
  if(credit==1){

   if(digitalRead(12)==HIGH && pag>1 && pressed==0)
       pag--,switcher(),pressed=1,delay(300);
   if(digitalRead(13)==HIGH && pag<14 && pressed==0)
       pag++,switcher(),pressed=1,delay(300);
   
  if(digitalRead(12)==LOW && digitalRead(13)==LOW)
      pressed=0;


   if(digitalRead(26)==HIGH)
      start=1,credit=0,timp=120,lcd.clear(), obiectecastigate=0, deridicat=0, ajustaresenzorisimediesenzori(),timptrecut=millis();
      
  }

  if(start==1){
     timer();
     if(cadere()==1 && deridicat==0){
        deridicat=1;
        pagfelicitari();
       // canteccadere();
       obiectecastigate++;
     }

     if(cadere()==0 && deridicat==1)
        deridicat=0,lcd.clear();

    if(analogRead(A0)>800 || analogRead(A1)>800 || analogRead(A0)<200 || analogRead(A1)<200)
      clearLEDs(),oxoy();
      
    if(digitalRead(7)==HIGH || digitalRead(6)==HIGH)
      clearLEDs(),oz();

    if(analogRead(potpin)!=potpoz)
      clearLEDs(),claw();
   
    if(millis()-timptrecut>1000){  
      timp = timp - (millis()-timptrecut)/1000;
      timptrecut=millis();
  }

    if(timp==0)
      start=0, digitalWrite(35,LOW), mesajfinal(), repozitionareoz();//cantecfinal();
  }

  if(credit==0 && start==0)
  {
    paganimatie0();
    delay(1000);
    paganimatie1();
    delay(1000);
 
  } 
}
