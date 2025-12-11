#include "LockSystem.h"
#include <Arduino.h>

LockSystem::LockSystem(int c1, int c2, int l1, int l2, int redPin, int greenPin, int keyPin, int connPin, int btn1, int btn2, int btn3, int btn4, int btn5, int btn6, int btn7, int btn8, int clk, int dio)
    : codeLED1(c1), codeLED2(c2), lockLED1(l1), lockLED2(l2),
      status(redPin, greenPin, connPin),
      display(btn1, btn2, btn3, btn4, btn5, btn6, btn7, btn8, clk, dio),
      locked(true), lastUpdate(0), fadeDelay(15),
      brightness1(128), brightness2(255),
      fadeStep(2), direction(1) {
        pinMode(keyPin, INPUT_PULLUP);
        setLocked(true);
        connected=false;
        status.begin();
        display.begin();
      }

void LockSystem::setLocked(bool state) {
    locked = state;
    status.setLocked(state);
}

void LockSystem::update() {
    int _key=digitalRead(keyPin);
    if (_key == HIGH) {
        setLocked(false); }
    else {
        setLocked(true);
    }
    unsigned long now = millis();

    status.update();
    display.update();

    if (now - lastUpdate > fadeDelay) {
        lastUpdate = now;

        // Opdater lysstyrker
        brightness1 += fadeStep * direction;
        brightness2 -= fadeStep * direction;

        // Tjek grænser (64–255)
        if (brightness1 >= 255 || brightness1 <= 64) {
            direction *= -1;  // Skift retning
        }
    }

    // Anvend PWM-værdier på de aktive LED’er
    if (locked) {
        lockLED1.setBrightness(brightness1);
        lockLED2.setBrightness(brightness2);
        codeLED1.setBrightness(0);
        codeLED2.setBrightness(0);
    } else {
        codeLED1.setBrightness(brightness1);
        codeLED2.setBrightness(brightness2);
        lockLED1.setBrightness(0);
        lockLED2.setBrightness(0);
    }
}
