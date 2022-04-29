#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows
MFRC522 mfrc522(SS_PIN, RST_PIN);

int pag=1;
int pressed=0;
int credit=0;

byte t[8] =                 /////
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


byte a1[8] =         ////
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

byte a[8] =             ////
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

byte i[8] =         /////
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


void setup()
{
  Serial.begin(9600);
  SPI.begin(); // Initiate SPI bus
  mfrc522.PCD_Init(); // Initiate MFRC522
  lcd.init(); // initialize the lcd
  lcd.backlight();
  
  lcd.createChar(3,t);
  lcd.createChar(4,a);
  lcd.createChar(5,i);
  lcd.createChar(7,a1);
}

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

  while(digitalRead(6)==LOW && digitalRead(7)==LOW)
  {
    animatie0();
    delay(400);
    animatie1();
    delay(400);
  }
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


void loop()
{

  if( mfrc522.PICC_IsNewCardPresent())       
            credit=1, pag1();
  
  if(credit==1){
   if(digitalRead(6)==HIGH && pag>1 && pressed==0)
       pag--,switcher(),pressed=1,delay(300);
   if(digitalRead(7)==HIGH && pag<14 && pressed==0)
       pag++,switcher(),pressed=1,delay(300);
   
  if(digitalRead(6)==LOW && digitalRead(7)==LOW)
      pressed=0;

  }
  
  else
  {
    paganimatie0();
    delay(1000);
    paganimatie1();
    delay(1000);
 
  }

  
   
  
}
