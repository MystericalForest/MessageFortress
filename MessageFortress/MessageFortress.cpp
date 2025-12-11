/**
 * MessageFortress.cpp
 * Hovedklasse der koordinerer alle subsystemer
 */

#include "MessageFortress.h"
#include "config.h"

/**
 * Konstruktør for MessageFortress
 * Initialiserer alle subsystemer med hardcoded pins
 */
MessageFortress::MessageFortress()
    : display(),
      keypad(),
      form(display, keypad),
      lockSys(CODE_LED_1_PIN, CODE_LED_2_PIN, LOCK_LED_1_PIN, LOCK_LED_2_PIN,
              STATUS_RED_PIN, STATUS_GREEN_PIN, KEY_PIN, CONNECTION_PIN,
              BUTTON_1_PIN, BUTTON_2_PIN, BUTTON_3_PIN, BUTTON_4_PIN,
              BUTTON_5_PIN, BUTTON_6_PIN, BUTTON_7_PIN, BUTTON_8_PIN,
              DISPLAY_CLK_PIN, DISPLAY_DIO_PIN),
      isLocked(true),
      displayEnabled(false),
      keyPin(KEY_PIN) {}

/**
 * Initialiser alle subsystemer
 */
void MessageFortress::begin() {
    pinMode(keyPin, INPUT_PULLUP);
    display.begin();
    updateDisplayState();
}

/**
 * Hovedupdate loop
 * Håndterer input og opdaterer alle systemer
 */
void MessageFortress::update() {
    // Tjek KEY_PIN for display on/off
    updateDisplayState();
    
    // Kun håndter input hvis display er tændt
    if (displayEnabled) {
        char key = keypad.getKey();
        if (key) {
            form.handleInput(key);
        }
    }
    
    // Opdater lock system
    lockSys.update();
}

/**
 * Opdaterer display tilstand baseret på KEY_PIN
 */
void MessageFortress::updateDisplayState() {
    bool keyPressed = (digitalRead(keyPin) == LOW);
    
    if (keyPressed && !displayEnabled) {
        // Tænd begge displays
        displayEnabled = true;
        display.turnOn();
        form.show();
        lockSys.getCodeDisplay().turnOn();
    } else if (!keyPressed && displayEnabled) {
        // Sluk begge displays
        displayEnabled = false;
        display.clear();
        lockSys.getCodeDisplay().turnOff();
    }
}