/**
 * AccessControl.cpp
 * Håndterer adgangskode logik og timeout funktionalitet
 */

#include "AccessControl.h"
#include "config.h"

/**
 * Konstruktør for AccessControl
 */
AccessControl::AccessControl()
  : _unlocked(false), _currentInput(0), _lastInputTime(0), _inputTimeout(5000) {}

/**
 * Initialiser AccessControl systemet
 */
void AccessControl::begin() {
  _unlocked = false;
  _currentInput = 0;
  _lastInputTime = millis();
}

/**
 * Håndterer input og tjekker adgangskode
 * @param input Button kombination som input
 */
void AccessControl::handleInput(int input) {
  if (input > 0) {
    _currentInput = input;
    _lastInputTime = millis();
    
    // Tjek om adgangskoden matcher
    if (_currentInput == ACCESS_CODE) {
      _unlocked = true;
    }
  }
  
  // Reset input efter timeout
  if (millis() - _lastInputTime > _inputTimeout) {
    _currentInput = 0;
  }
}

/**
 * Returnerer om systemet er låst op
 */
bool AccessControl::isUnlocked() {
  return _unlocked;
}

/**
 * Låser systemet igen
 */
void AccessControl::lock() {
  _unlocked = false;
  _currentInput = 0;
}

/**
 * Returnerer nuværende input
 */
int AccessControl::getCurrentInput() {
  return _currentInput;
}

/**
 * Tjekker om input har timeout
 */
bool AccessControl::hasTimedOut() {
  return (millis() - _lastInputTime) > _inputTimeout;
}