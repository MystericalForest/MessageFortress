#ifndef CODE_DISPLAY_H
#define CODE_DISPLAY_H

#include <Arduino.h>
#include <TM1637Display.h>

class CodeDisplay {
  private:
    int _btn1, _btn2, _btn3;
    int _clk, _dio;
    TM1637Display _display;

    int readInputs();
    int getCode();

  public:
    CodeDisplay(int btn1, int btn2, int btn3, int clk, int dio);
    void begin();
    void update();
};

#endif
