#ifndef CODE_DISPLAY_H
#define CODE_DISPLAY_H

#include <Arduino.h>
#include <TM1637Display.h>
#include "ButtonInput.h"
#include "AccessControl.h"
#include "CodeMapper.h"

/**
 * CodeDisplay klasse (refaktoreret)
 * Håndterer kun 7-segment display funktionalitet
 */
class CodeDisplay {
private:
    TM1637Display _display;
    ButtonInput _buttonInput;
    AccessControl _accessControl;
    CodeMapper _codeMapper;

public:
    CodeDisplay(int btn1, int btn2, int btn3, int btn4, int btn5, int btn6, int btn7, int btn8, int clk, int dio);
    void begin();
    void update();
    bool isUnlocked();
};

#endif
