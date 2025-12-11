#ifndef MESSAGEFORTRESS_H
#define MESSAGEFORTRESS_H

#include "LockSystem.h"
#include "DisplayManager.h"
#include "KeypadManager.h"
#include "FormManager.h"

/**
 * MessageFortress hovedklasse
 * Indkapsler alle subsystemer og forenkler interface
 */
class MessageFortress {
private:
    DisplayManager display;
    KeypadManager keypad;
    FormManager form;
    LockSystem lockSys;
    bool isLocked;
    bool displayEnabled;
    int keyPin;

public:
    MessageFortress();
    void begin();
    void update();
    void updateDisplayState();
};

#endif