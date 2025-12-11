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
      isLocked(true) {}

/**
 * Initialiser alle subsystemer
 */
void MessageFortress::begin() {
    display.begin();
    form.show();
}

/**
 * Hovedupdate loop
 * Håndterer input og opdaterer alle systemer
 */
void MessageFortress::update() {
    // Håndter keypad input
    char key = keypad.getKey();
    if (key) {
        form.handleInput(key);
    }
    
    // Opdater lock system
    lockSys.update();
}