#include <Stepper.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

#define dirPinox 2 ///nema17
#define stepPinox 3
#define dirPinoy 4
#define stepPinoy 5
#define stepsPerRevolution 500
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
int oxpozitie=0;
int oypozitie=0;
double ozpozitie=0;

int potpin =8; // pin analog conectare potentiometru
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

#define OCTAVE_OFFSET 0
#define isdigit(n) (n >= '0' && n <= '9')

const int tonePin = 24;

int notes[] = { 0,
                262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494,
                523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988,
                1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976,
                2093, 2217, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 3520, 3729, 3951
              };

char *piesaintro = "FinalFan:d=4,o=5,b=112:16a4,16a4,16a4,8c.,16a4,16a4,16a4,8d.,16a4,16a4,16a4,16d#,16d,16c,16d,16c,16b4,8c,16b4,16a4,16a4,16a4,8c.,16a4,16a4,16a4,8d.,16a4,16a4,16a4,16d#,16d,16c,16d,16c,16b4,8c,16b4,16c,16c,16c,8d#.,16c,16c,16c,8f.,16c,16c,16c,16f#,16f,16d#,16f,16d#,16d,8d#,16d,16c,16c,16c,8d#.,16c,16c,16c,8f.,16c,16c,16c,16f#,16f,16d#,16f,16d#,16d,16d#,16d,16c";
char *piesaapasat= "ChocoboT:d=4,o=6,b=160:32c5,32d5,32e5,32f5,32g5,32a5,32b5,32c,32d,32e,32f,32g,32a,32b,32c7,16d7,8p,8b,8g,8e,8d7,8b,8g,8b,8p,8g,8p,b,8p";
char *piesacazut = "DuHast:d=4,o=6,b=160:16a,16g,16d,16p,16f,16p,16e,16p,8a5,16d,16f,16g,16p,16e,8p,16a,16g,16d,16f,16e,16a5,16e,16f,16g,8e";
char *piesafinal = "SuperMar:d=16,o=6,b=112:e,32p,8e,c,8e,8g,8g5,8c,p,8g5,p,8e5,p,8a5,8b5,a#5,8a5,g.5,e,g,8a,f,8g,8e,c,d,8b5,p,8c,p,8g5,p,8e5,p,8a5,8b5,a#5,8a5,g.5,e,g,8a,f,8g,8e";
char *piesacredit = "Theme:d=4,o=5,b=112:32f#6,32g6,32p,32g6,32g#6,32a6,32p,32b.6";


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
  SPI.begin();
  mfrc522.PCD_Init(); 
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
  digitalWrite(35,HIGH);
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

  play_rtttl(piesacazut);

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
  lcd.print("Nu ai castigat:(");
  lcd.setCursor(0,1);
  lcd.print("Mai incearca!");
  }
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
  delay(100);
  valn1=0;
  valn2=0;
  valn3=0;
  valn4=0;
  for(int i=1;i<=5;i++){
    delay(90);
    valn1=valn1+analogRead(sen1);
    valn2=valn2+analogRead(sen2);
    valn3=valn3+analogRead(sen3);
    valn4=valn4+analogRead(sen4);
  }
  valn1=valn1/5;
  valn2=valn2/5;
  valn3=valn3/5;
  valn4=valn4/5;
}

int cadere(){

  if(analogRead(sen1)+100<=valn1)
    return 1;

  if(analogRead(sen2)+100<=valn2)
    return 1;

  if(analogRead(sen3)+100<=valn3)
    return 1;
  
  if(analogRead(sen4)+100<=valn4)
    return 1;
  
   return 0;
}

//Buzzer

void play_rtttl(char *p)
{
  byte default_dur = 4;
  byte default_oct = 6;
  int bpm = 63;
  int num;
  long wholenote;
  long duration;
  byte note;
  byte scale;

  while (*p!=':') p++; 
  p++;                

  if (*p == 'd')
  {
    p++; p++;       
    num = 0;
    while (isdigit(*p))
    {
      num = (num * 10) + (*p++ - '0');
    }
    if (num > 0) default_dur = num;
    p++;                  
  }

  // get default octave
  if (*p == 'o')
  {
    p++; p++;              
    num = *p++ - '0';
    if (num >= 3 && num <= 7) default_oct = num;
    p++;                   
  }

  // get BPM
  if (*p == 'b')
  {
    p++; p++;             
    num = 0;
    while (isdigit(*p))
    {
      num = (num * 10) + (*p++ - '0');
    }
    bpm = num;
    p++;                  
  }

  wholenote = (60 * 1000L / bpm) * 4;  


  while (*p)
  {

    num = 0;
    while (isdigit(*p))
    {
      num = (num * 10) + (*p++ - '0');
    }

    if (num) duration = wholenote / num;
    else duration = wholenote / default_dur;  

    note = 0;

    switch (*p)
    {
      case 'c':
        note = 1;
        break;
      case 'd':
        note = 3;
        break;
      case 'e':
        note = 5;
        break;
      case 'f':
        note = 6;
        break;
      case 'g':
        note = 8;
        break;
      case 'a':
        note = 10;
        break;
      case 'b':
        note = 12;
        break;
      case 'p':
      default:
        note = 0;
    }
    p++;

    
    if (*p == '#')
    {
      note++;
      p++;
    }

    
    if (*p == '.')
    {
      duration += duration / 2;
      p++;
    }

    
    if (isdigit(*p))
    {
      scale = *p - '0';
      p++;
    }
    else
    {
      scale = default_oct;
    }

    scale += OCTAVE_OFFSET;

    if (*p == ',')
      p++;       
      
    if (note)
    {
      tone(tonePin, notes[(scale - 4) * 12 + note]);
      delay(duration);
      noTone(tonePin);
    }
    else
    {
      delay(duration);
    }
  }
}



void oxmovement()
{
   for (int i = 0; i < 100; i++) {
   digitalWrite(stepPinox, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPinox, LOW);
    delayMicroseconds(450);  }
    
  
}

void oymovement()
{
   for (int i = 0; i < 100; i++) {
    digitalWrite(stepPinoy, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPinoy, LOW);
    delayMicroseconds(450);}
 
 
  
}

void repozitionarexoy(){

  while(!(oxpozitie==0))
      digitalWrite(dirPinox, LOW),oxpozitie=oxpozitie-1,oxmovement();

  while(!(oypozitie==0))
      digitalWrite(dirPinoy, HIGH),oypozitie=oypozitie-1,oymovement();

}

void oxoy()
{
  OX=analogRead(A0);
  OY=analogRead(A1);

  if(OX<50 && oxpozitie<12)
    digitalWrite(dirPinox, HIGH), oxpozitie=oxpozitie+1, oxmovement();

  if(OX>900 && oxpozitie>0)
    digitalWrite(dirPinox, LOW),oxpozitie=oxpozitie-1,oxmovement();

  if(OY<50 && oypozitie>0)
    digitalWrite(dirPinoy, HIGH),oypozitie=oypozitie-1,oymovement();
   
  if(OY>900 && oypozitie<16)
  digitalWrite(dirPinoy, LOW),oypozitie=oypozitie+1,oymovement();
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
   while(digitalRead(6)==HIGH){    //injos  && (ozpozitie>=-20 && ozpozitie<=8000)
    
     if(ozpozitie>=3100)
        ozpozitie=3101;
        
     if(ozpozitie<=3100)
        counterclockwise(),ozpozitie=ozpozitie+0.25;          
    }          
  
   while(digitalRead(7)==HIGH){ 

      if(ozpozitie<=-3100)
        ozpozitie=-3101;
    
     if(ozpozitie>=-3100)
       clockwise(),ozpozitie=ozpozitie-0.25;
}
}


void repozitionareoz(){
   
   while(!(ozpozitie>=-1 && ozpozitie<=1)){
   if(ozpozitie>0)
       clockwise(),ozpozitie=ozpozitie-0.25;

   if(ozpozitie<0)
         counterclockwise(),ozpozitie=ozpozitie+0.25;
}
}

void claw()
{
  int servopoz;
  potpoz = analogRead(potpin);
  servopoz = map(potpoz, 0, 1023, 29, 65); // scalare in intervalul 0...180
  myservo.write(servopoz); // setare pozitie servo
  delay(10); // asteptare rotire servo

  
}


void loop() {

  if(mfrc522.PICC_IsNewCardPresent() && credit==0 && start==0)       
       credit=1, pag1(), play_rtttl(piesacredit);
  
  if(credit==1){

   if(digitalRead(13)==HIGH && pag>1 && pressed==0)
       pag--,switcher(),pressed=1,delay(300);
   if(digitalRead(12)==HIGH && pag<14 && pressed==0)
       pag++,switcher(),pressed=1,delay(300);
   
  if(digitalRead(12)==LOW && digitalRead(13)==LOW)
      pressed=0;


   if(digitalRead(26)==HIGH)
      start=1,credit=0,timp=120,lcd.clear(), obiectecastigate=0, deridicat=0, ajustaresenzorisimediesenzori(), play_rtttl(piesaapasat),timptrecut=millis();
      
  }

  if(start==1){
     timer();
     
     if(cadere()==1 && deridicat==0){
        lcd.clear();
        clearLEDs();
        deridicat=1;
        pagfelicitari();
        obiectecastigate++;
     }

     if(cadere()==0 && deridicat==1)
        deridicat=0,lcd.clear();

    while(analogRead(A0)>900 || analogRead(A1)>900 || analogRead(A0)<150 || analogRead(A1)<150)
      clearLEDs(),oxoy();
      
    if(digitalRead(7)==HIGH || digitalRead(6)==HIGH)
      clearLEDs(),oz();

    if(analogRead(potpin)!=potpoz)
      clearLEDs(),claw();
   
    if(millis()-timptrecut>1000){  
      timp = timp - (millis()-timptrecut)/1000;
      timptrecut=millis();
  }

    if(timp<=0)
      start=0,clearLEDs(), mesajfinal(), play_rtttl(piesafinal), repozitionarexoy(),repozitionareoz();
  }

  if(credit==0 && start==0)
  {
    paganimatie0();
    delay(1000);
    paganimatie1();
    delay(1000);
 
  } 
}
