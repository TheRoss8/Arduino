#include <Wire.h>
#include <LiquidCrystal_I2C.h> 


const int res = A3;
const int button = 2;
const int fan = 3;
unsigned long prev = 0;
int controller = 0;
int minutes;
int cnt = 0;
String t = " min";
String r = "Remaining";

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  
  pinMode (res, INPUT);
  pinMode (button, INPUT);
  pinMode (fan, OUTPUT);

  lcd.init();
}

void loop() {
  int val;
  switch(controller){
    case 0:
      digitalWrite(fan, LOW);
      lcd.backlight();
      val = analogRead(res)/32;
      lcd.setCursor(0,0);
      lcd.print("Set Timer");
      lcd.setCursor(0,1);
      lcd.print(val);
      lcd.print(t);
      if(digitalRead(button) == HIGH){
        minutes = val;
        controller = 1;
        delay(500);
        prev = millis();
      }
      delay(20);
      lcd.clear();
      break;
      
    case 1:
      if(cnt == 0){
        lcd.clear();
        digitalWrite(fan, HIGH);
        lcd.print(r);
        lcd.setCursor(0,1);
        lcd.print(minutes);
        lcd.print(t);
        cnt++;
      }
      if(millis() - prev >= 60000){
        prev = millis();
        minutes--;
        lcd.noBacklight();
          if(minutes <= 0)
            controller = 2;
        cnt = 0;
      }
      if(digitalRead(button) == HIGH){
        cnt = 0;
        controller = 0;
        delay(500);
      }
      break;

   case 2:
    if(cnt == 0){
      digitalWrite(fan, LOW);
      lcd.noBacklight();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Press button to");
      lcd.setCursor(0,1);
      lcd.print("resume");
      cnt++;
    }
    if(digitalRead(button) == HIGH){
      cnt = 0;
      controller = 0;
      delay(500);
    }
    break;
  }

}
