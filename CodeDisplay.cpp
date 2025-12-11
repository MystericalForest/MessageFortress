#include "CodeDisplay.h"

CodeDisplay::CodeDisplay(int btn1, int btn2, int btn3, int btn4, int btn5, int btn6, int btn7, int btn8, int clk, int dio)
  : _btn1(btn1), _btn2(btn2), _btn3(btn3), _btn4(btn4), _btn5(btn5), _btn6(btn6), _btn7(btn7), _btn8(btn8), _clk(clk), _dio(dio), _display(clk, dio) {}

void CodeDisplay::begin() {
  pinMode(_btn1, INPUT_PULLUP);
  pinMode(_btn2, INPUT_PULLUP);
  pinMode(_btn3, INPUT_PULLUP);
  pinMode(_btn4, INPUT_PULLUP);
  pinMode(_btn5, INPUT_PULLUP);
  pinMode(_btn6, INPUT_PULLUP);
  pinMode(_btn7, INPUT_PULLUP);
  pinMode(_btn8, INPUT_PULLUP);
  _display.setBrightness(0x0f);
}

int CodeDisplay::readInputs() {
  int a = digitalRead(_btn1);
  int b = digitalRead(_btn2);
  int c = digitalRead(_btn3);
  int d = digitalRead(_btn4);
  int e = digitalRead(_btn5);
  int f = digitalRead(_btn6);
  int g = digitalRead(_btn7);
  int h = digitalRead(_btn8);
  return (h << 7) | (g << 6) | (f << 5) | (e << 4) | (d << 3) | (c << 2) | (b << 1) | a;
}

int CodeDisplay::getCode() {
  switch (readInputs()) {
    case 0: return 1234;
    case 1: return 1243;
    case 2: return 1423;
    case 3: return 1432;
    case 4: return 4123;
    case 5: return 4231;
    case 6: return 4321;
    case 7: return 4312;
    case 8: return 1234;
    case 9: return 3243;
    case 10: return 3423;
    case 11: return 3432;
    case 12: return 3123;
    case 13: return 3231;
    case 14: return 3321;
    case 15: return 4352;
    case 16: return 5432;
    case 17: return 5123;
    case 18: return 5231;
    case 19: return 5321;
    case 20: return 5312;
    case 21: return 3543;
    case 22: return 3512;
    case 23: return 3523;
    case 24: return 3532;
    case 25: return 4535;
    case 26: return 4532;
    case 27: return 1523;
    case 28: return 2531;
    case 29: return 3521;
    case 30: return 3512;
    case 31: return 3523;
    case 32: return 3522;
    default: return 0;
  }
}

void CodeDisplay::update() {
  int code = getCode();
  _display.showNumberDec(code, false);
}
