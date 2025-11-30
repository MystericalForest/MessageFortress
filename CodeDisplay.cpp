#include "CodeDisplay.h"

NEW SKETCH

CodeDisplay::CodeDisplay(int btn1, int btn2, int btn3, int clk, int dio)
  : _btn1(btn1), _btn2(btn2), _btn3(btn3), _clk(clk), _dio(dio), _display(clk, dio) {}

void CodeDisplay::begin() {
  pinMode(_btn1, INPUT_PULLUP);
  pinMode(_btn2, INPUT_PULLUP);
  pinMode(_btn3, INPUT_PULLUP);
  _display.setBrightness(0x0f);
}

int CodeDisplay::readInputs() {
  int a = digitalRead(_btn1);
  int b = digitalRead(_btn2);
  int c = digitalRead(_btn3);
  return (c << 2) | (b << 1) | a;
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
    default: return 0;
  }
}

void CodeDisplay::update() {
  int code = getCode();
  _display.showNumberDec(code, false);
}
