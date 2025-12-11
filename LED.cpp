#include "LED.h"
#include <Arduino.h>

LED::LED(int p) : pin(p) {
    pinMode(pin, OUTPUT);
}

void LED::setBrightness(int value) {
    analogWrite(pin, constrain(value, 0, 255));
}
