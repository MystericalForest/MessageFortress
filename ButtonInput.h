#ifndef BUTTONINPUT_H
#define BUTTONINPUT_H

#include <Arduino.h>

/**
 * ButtonInput klasse
 * Håndterer læsning af 8 knapper og konverterer til binær værdi
 */
class ButtonInput {
private:
    int _btn1, _btn2, _btn3, _btn4, _btn5, _btn6, _btn7, _btn8;
    int _lastReading;
    unsigned long _lastDebounceTime;
    int _debounceDelay;

public:
    ButtonInput(int btn1, int btn2, int btn3, int btn4, int btn5, int btn6, int btn7, int btn8);
    void begin();
    int readInputs();
    bool hasChanged();
};

#endif