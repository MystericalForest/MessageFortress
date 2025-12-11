#ifndef CODE_DISPLAY_H
#define CODE_DISPLAY_H

#include <Arduino.h>
#include <TM1637Display.h>

class CodeDisplay {
  private:
    int _btn1, _btn2, _btn3, _btn4, _btn5, _btn6, _btn7, _btn8;
    int _clk, _dio;
    TM1637Display _display;

    int readInputs();
    int getCode();

  public:
    CodeDisplay(int btn1, int btn2, int btn3, int btn4, int btn5, int btn6, int btn7, int btn8, int clk, int dio);
    void begin();
    void update();
    void turnOff();
    void turnOn();
};

#endif
