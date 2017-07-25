#include <Wire.h>
#include <LiquidCrystal_I2C.h> 
#include <DHT.h> 
const int DHT_PIN=7;
const long interval=10000;
const int RED=8, GREEN=9, BLUE=10;
const int MIN=19, MAX=23;
unsigned long prevMill=0;
unsigned long currMill;
int temp;
int hum;
LiquidCrystal_I2C lcd(0x27,16,2);
DHT sens(DHT_PIN,11);
void setup()
{
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("TEMP:");
  lcd.setCursor(0,1);
  lcd.print("HUM:");
  sens.begin();
}
void loop()
{
  currMill=millis();
  if(currMill-prevMill>=interval){
    prevMill=currMill;
    temp= sens.readTemperature();
    hum= sens.readHumidity();
    lcd.setCursor(8,0);
    lcd.print(temp);
    lcd.print((char)223);
    lcd.print("C");
    lcd.setCursor(8,1);
    lcd.print(hum);
    lcd.print("%");
    }
  if(temp<MIN){
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, LOW);
    digitalWrite(10, HIGH);
  }
  else if(temp>MAX){
    digitalWrite(8, HIGH);
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, LOW);
  }
  else{
    digitalWrite(RED, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(BLUE, LOW);
  }
}
