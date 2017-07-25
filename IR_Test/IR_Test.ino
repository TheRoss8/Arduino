#include <IRremote.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

const int irPin= 3;
const int one= 0xFF30CF;
const int two= 0xFF18E7;
const int three= 0xFF7A85;
const int four= 0xFF10EF;
const int five= 0xFF38C7;
const int six= 0xFF5AA5;
const int seven= 0xFF42BD;
const int eight= 0xFF4AB5;
const int nine= 0xFF52AD;

IRrecv irReceiver(irPin);
decode_results signals;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  lcd.init();
  lcd.backlight();
  irReceiver.enableIRIn();
  lcd.print("CIAO");
}
void loop() {
 if(irReceiver.decode(&signals)) {
  switch(signals.value){
    case one: {lcd.print(1);
               break;}
    case two: {lcd.print(2);
               break;}
    case three: {lcd.print(3);
                 break;}
    case four: {lcd.print(4);
                break;}
    case five: {lcd.print(5);
                break;}
    case six: {lcd.print(6);
               break;}
    case seven: {lcd.print(7);
                 break;}
    case eight: {lcd.print(8);
                 break;}
    case nine: {lcd.print(9);
                break;}
    default: {lcd.print("NaN");
            break;}
    }
  irReceiver.resume();
 }
}
