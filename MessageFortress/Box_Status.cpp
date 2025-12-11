#include "Box_Status.h"

Box_Status::Box_Status(uint8_t redPin, uint8_t greenPin, uint8_t connPin)
: _redPin(redPin), _greenPin(greenPin), _connPin(connPin),
  _currentState(NOT_CONNECTED), _lastKnownState(LOCKED),
  _lastBlinkTime(0), _redLedState(false)
{}

void Box_Status::begin() {
    pinMode(_redPin, OUTPUT);
    pinMode(_greenPin, OUTPUT);
    pinMode(_connPin, INPUT_PULLUP);  // Brug intern pullup
    applyState();
}

void Box_Status::setState(State newState) {
    // Hvis boksen er connected, opdater tilstanden
    if (isConnected()) {
        _currentState = newState;

        // Gem kun locked/unlocked som "sidst kendte" tilstand
        if (newState == LOCKED || newState == UNLOCKED) {
            _lastKnownState = newState;
        }

        applyState();
    }
}

void Box_Status::setLocked(bool locked) {
  if (locked) {
    setState(LOCKED);
  } else {
    setState(UNLOCKED);
  }
}

Box_Status::State Box_Status::getStatus() const {
    return _currentState;
}

bool Box_Status::isConnected() {
    // Kontakt trækker til GND når forbundet
    return digitalRead(_connPin) == LOW;
}

void Box_Status::applyState() {
    digitalWrite(_redPin, LOW);
    digitalWrite(_greenPin, LOW);
    _lastBlinkTime = millis();
    _redLedState = false;
}

void Box_Status::update() {
    // Check forbindelsen først
    if (!isConnected()) {
        _currentState = NOT_CONNECTED;
    } else {
        // Hvis den lige er blevet connected igen, genskab sidste kendte status
        if (_currentState == NOT_CONNECTED) {
            _currentState = _lastKnownState;
            applyState();
        }
    }

    switch (_currentState) {
        case NOT_CONNECTED: {
            unsigned long currentTime = millis();
            if (currentTime - _lastBlinkTime >= 500) { // blink hvert 500 ms
                _redLedState = !_redLedState;
                digitalWrite(_redPin, _redLedState);
                _lastBlinkTime = currentTime;
            }
            digitalWrite(_greenPin, LOW);
            break;
        }

        case LOCKED:
            digitalWrite(_redPin, HIGH);
            digitalWrite(_greenPin, LOW);
            break;

        case UNLOCKED:
            digitalWrite(_redPin, LOW);
            digitalWrite(_greenPin, HIGH);
            break;
    }
}
