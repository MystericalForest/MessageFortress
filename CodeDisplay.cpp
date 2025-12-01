/**
 * CodeDisplay.cpp (refaktoreret)
 * Håndterer kun 7-segment display funktionalitet
 * Bruger modulære klasser for button input, adgangskode og kode mapping
 */

#include "CodeDisplay.h"
#include "config.h"

/**
 * Konstruktør for CodeDisplay
 * @param btn1-btn8 Button pins (8 knapper)
 * @param clk, dio TM1637 display pins
 */
CodeDisplay::CodeDisplay(int btn1, int btn2, int btn3, int btn4, int btn5, int btn6, int btn7, int btn8, int clk, int dio)
  : _display(clk, dio),
    _buttonInput(btn1, btn2, btn3, btn4, btn5, btn6, btn7, btn8),
    _accessControl(),
    _codeMapper() {}

/**
 * Initialiser CodeDisplay systemet
 * Initialiserer alle modulære komponenter
 */
void CodeDisplay::begin() {
  _buttonInput.begin();           // Initialiser button input
  _accessControl.begin();         // Initialiser adgangskode kontrol
  _display.setBrightness(DISPLAY_BRIGHTNESS);  // Sæt display lysstyrke
}

/**
 * Returnerer om systemet er låst op
 */
bool CodeDisplay::isUnlocked() {
  return _accessControl.isUnlocked();
}

/**
 * Opdaterer displayet med den aktuelle kode eller adgangskode prompt
 * Kaldes kontinuerligt fra hovedloop
 */
void CodeDisplay::update() {
  int input = _buttonInput.readInputs();
  
  if (!_accessControl.isUnlocked()) {
    // Håndter adgangskode input
    _accessControl.handleInput(input);
    
    // Vis nuværende input eller prompt
    int currentInput = _accessControl.getCurrentInput();
    if (currentInput > 0) {
      _display.showNumberDec(currentInput, false);
    } else {
      _display.showNumberDec(0, false);  // Vis 0000 som prompt
    }
  } else {
    // Normal kode visning når låst op
    int code = _codeMapper.getCode(input);
    _display.showNumberDec(code, false);
  }
}
