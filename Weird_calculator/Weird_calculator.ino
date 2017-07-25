#include <SevSeg.h>
SevSeg disp;

const byte IN = A5, BUTTON = 13;
int oper, f1 = 0, f2 = 0, i = 0;

void setup() {
  const byte DIGITS = 4;
  const byte DIGPIN[] = {1, 2, 3, 4};
  const byte SEG[] = {6, 7, 8, 9, 10, 11, 12, 13};
  
  disp.begin(COMMON_CATHODE, DIGITS, DIGPIN, SEG);
  disp.setBrightness(10);
  Serial.begin(9600);
  
  pinMode (IN, INPUT);
  pinMode (BUTTON, INPUT);
}

void loop() {
    switch(i){
      case 0:
        disp.setNumber(getNum() * 100);
        if(digitalRead(BUTTON) == HIGH) {
          f1+= getNum() * 100;
          i++;
          delay(300);
        }
        break;
      case 1:
        disp.setNumber(f1 + getNum() * 10);
        if(digitalRead(BUTTON) == HIGH) {
          f1+= getNum() * 10;
          delay(300);
          i++;
        }
        break;
      case 2:
        disp.setNumber(f1 + getNum());
        if(digitalRead(BUTTON) == HIGH) {
          f1+= getNum();
          delay(300);
          i++;
        }
        break;
      case 3:
        disp.setNumber(getOperand());
        if(digitalRead(BUTTON) == HIGH) {
          oper = getOperand();
          i++;
          delay(300);
        }
        break;
      case 4:
        disp.setNumber(getNum() * 100);
        if(digitalRead(BUTTON) == HIGH) {
          f2+= getNum() * 100;
          i++;
          delay(300);
        }
        break;
      case 5:
        disp.setNumber(f2 + getNum() * 10);
        if(digitalRead(BUTTON) == HIGH) {
          f2+= getNum() * 10;
          i++;
          delay(300);
        }
        break;
      case 6:
        disp.setNumber(f2 + getNum());
        if(digitalRead(BUTTON) == HIGH) {
          f2+= getNum();
          i++;
          delay(300);
        }
        break;
      case 7:
        switch(oper){
          case 0: disp.setNumber(f1+f2); break;
          case 1: disp.setNumber(f1-f2); break;
          case 2: disp.setNumber(f1*f2); break;
          case 3: disp.setNumber(f1/f2); break;
        }
        break;
    }
  disp.refreshDisplay();
}

int getNum(){
  int currNum;
  if(analogRead(IN) < 100)
    currNum = 0;
  if(analogRead(IN) >= 100 && analogRead(IN) < 200)
    currNum = 1;
  if(analogRead(IN) >= 200 && analogRead(IN) < 300)
    currNum = 2;
  if(analogRead(IN) >= 300 && analogRead(IN) < 400)
    currNum = 3;
  if(analogRead(IN) >= 400 && analogRead(IN) < 500)
    currNum = 4;
  if(analogRead(IN) >= 500 && analogRead(IN) < 600)
    currNum = 5;
  if(analogRead(IN) >= 600 && analogRead(IN) < 700)
    currNum = 6;
  if(analogRead(IN) >= 700 && analogRead(IN) < 800)
    currNum = 7;
  if(analogRead(IN) >= 800 && analogRead(IN) < 900)
    currNum = 8;
  if(analogRead(IN) >= 900)
    currNum = 9;
  return currNum;
}

int getOperand(){
  int currOp;
  if(analogRead(IN) < 250)
    currOp = 0;
  if(analogRead(IN) >= 250 && analogRead(IN) < 500)
    currOp = 1;
  if(analogRead(IN) >= 500 && analogRead(IN) < 750)
    currOp = 2;
  if(analogRead(IN) >= 750)
    currOp = 3;
  return currOp;
}

