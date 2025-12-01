#ifndef ACCESSCONTROL_H
#define ACCESSCONTROL_H

#include <Arduino.h>

/**
 * AccessControl klasse
 * Håndterer adgangskode logik og unlock/lock tilstand
 */
class AccessControl {
private:
    bool _unlocked;
    int _currentInput;
    unsigned long _lastInputTime;
    int _inputTimeout;

public:
    AccessControl();
    void begin();
    void handleInput(int input);
    bool isUnlocked();
    void lock();
    int getCurrentInput();
    bool hasTimedOut();
};

#endif