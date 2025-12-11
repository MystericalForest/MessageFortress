#include "LockSystem.h"
#include "DisplayManager.h"
#include "KeypadManager.h"
#include "FormManager.h"

// Globale objekter
DisplayManager display;
KeypadManager keypad;
FormManager form(display, keypad);
LockSystem lockSys(2, 3, 4, 5, 8, 7, 12, 9, 42, 43, 44, 45, 46, 47, 48, 49, 10, 11);

bool isLocked = true;
unsigned long lastSwitch = 0;
int switchDelay = 5000; // Skift hver 5 sekunder

void setup() {
    display.begin();
    form.show();
    lockSys.setLocked(isLocked);
}

void loop() {
    char key = keypad.getKey();
    if (key) {
        form.handleInput(key);
    }
    lockSys.update();

    // Skift mellem låst og kodevisning
    unsigned long now = millis();
    if (now - lastSwitch > switchDelay) {
        isLocked = !isLocked;
     //   lockSys.setLocked(isLocked);
        lastSwitch = now;
    }
}
