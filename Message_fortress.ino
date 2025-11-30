#include "LockSystem.h"

LockSystem lockSys(2, 3, 4, 5, 8, 7, 9, 22, 23, 24, 10, 11);
bool isLocked = true;
unsigned long lastSwitch = 0;
int switchDelay = 5000; // Skift hver 5 sekunder

void setup() {
    lockSys.setLocked(isLocked);
}

void loop() {
    lockSys.update();

    // Skift mellem låst og kodevisning
    unsigned long now = millis();
    if (now - lastSwitch > switchDelay) {
        isLocked = !isLocked;
        lockSys.setLocked(isLocked);
        lastSwitch = now;
    }
}
