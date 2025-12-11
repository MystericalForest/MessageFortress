#ifndef KEYPAD_MANAGER_H
#define KEYPAD_MANAGER_H

#include <Keypad.h>
#include <Arduino.h>

class KeypadManager {
private:
  static const byte ROWS = 4;
  static const byte COLS = 4;
  char keys[ROWS][COLS];
  byte colPins[COLS];
  byte rowPins[ROWS];
  Keypad keypad;
public:
  KeypadManager();
  char getKey();
};

#endif
