/**
 * ButtonInput.cpp
 * Håndterer læsning af 8 knapper med debouncing
 */

#include "ButtonInput.h"
#include "config.h"

/**
 * Konstruktør for ButtonInput
 * @param btn1-btn8 Button pins
 */
ButtonInput::ButtonInput(int btn1, int btn2, int btn3, int btn4, int btn5, int btn6, int btn7, int btn8)
  : _btn1(btn1), _btn2(btn2), _btn3(btn3), _btn4(btn4), _btn5(btn5), _btn6(btn6), _btn7(btn7), _btn8(btn8),
    _lastReading(0), _lastDebounceTime(0), _debounceDelay(50) {}

/**
 * Initialiser alle button pins
 */
void ButtonInput::begin() {
  pinMode(_btn1, INPUT_PULLUP);
  pinMode(_btn2, INPUT_PULLUP);
  pinMode(_btn3, INPUT_PULLUP);
  pinMode(_btn4, INPUT_PULLUP);
  pinMode(_btn5, INPUT_PULLUP);
  pinMode(_btn6, INPUT_PULLUP);
  pinMode(_btn7, INPUT_PULLUP);
  pinMode(_btn8, INPUT_PULLUP);
}

/**
 * Læser alle 8 knapper og returnerer binær værdi (0-255)
 * @return 8-bit værdi med debouncing
 */
int ButtonInput::readInputs() {
  int btn1 = digitalRead(_btn1);
  int btn2 = digitalRead(_btn2);
  int btn3 = digitalRead(_btn3);
  int btn4 = digitalRead(_btn4);
  int btn5 = digitalRead(_btn5);
  int btn6 = digitalRead(_btn6);
  int btn7 = digitalRead(_btn7);
  int btn8 = digitalRead(_btn8);
  
  // Kombiner til 8-bit værdi (inverteret da pullup giver LOW når trykket)
  int reading = ((~btn8 & 1) << 7) | ((~btn7 & 1) << 6) | ((~btn6 & 1) << 5) | ((~btn5 & 1) << 4) |
                ((~btn4 & 1) << 3) | ((~btn3 & 1) << 2) | ((~btn2 & 1) << 1) | (~btn1 & 1);
  
  // Debouncing
  if (reading != _lastReading) {
    _lastDebounceTime = millis();
  }
  
  if ((millis() - _lastDebounceTime) > _debounceDelay) {
    _lastReading = reading;
    return reading;
  }
  
  return _lastReading;
}

/**
 * Tjekker om input har ændret sig
 */
bool ButtonInput::hasChanged() {
  int current = readInputs();
  return current != _lastReading;
}