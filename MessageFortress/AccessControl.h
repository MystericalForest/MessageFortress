#ifndef ACCESSCONTROL_H
#define ACCESSCONTROL_H

#include "DisplayManager.h"
#include "KeypadManager.h"
#include <Arduino.h>

/**
 * AccessControl klasse
 * Håndterer adgangskode funktionalitet før adgang til hovedsystem
 */
class AccessControl {
private:
    DisplayManager& display;
    KeypadManager& keypad;
    String currentInput;
    bool accessGranted;
    bool showingError;
    unsigned long errorStartTime;

public:
    AccessControl(DisplayManager& disp, KeypadManager& key);
    void begin();
    void handleInput(char key);
    void update();
    bool isAccessGranted();
    void showPrompt();
};

#endif