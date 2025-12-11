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
      accessControl(display, keypad),
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
    
    // Tjek KEY_PIN status ved opstart og sæt displays korrekt
    bool keyPressed = (digitalRead(keyPin) == LOW);
    if (keyPressed) {
        // KEY_PIN er trykket ved opstart - tænd kun LCD display
        displayEnabled = true;
        display.turnOn();
        // CodeDisplay tændes først efter korrekt adgangskode
    } else {
        // KEY_PIN ikke trykket ved opstart - hold displays slukket
        displayEnabled = false;
        display.clear();
        lockSys.getCodeDisplay().turnOff();
    }
}

/**
 * Hovedupdate loop
 * Håndterer input og opdaterer alle systemer
 */
void MessageFortress::update() {
    // Tjek KEY_PIN for display on/off
    updateDisplayState();
    
    // Opdater startup sekvens hvis aktiv
    if (display.isStartupActive()) {
        display.updateStartup();
        // Tjek om startup lige er blevet færdig
        if (!display.isStartupActive()) {
            accessControl.showPrompt();  // Vis adgangskode prompt når startup er færdig
        }
    }
    
    // Opdater AccessControl (for fejlbesked timer)
    if (displayEnabled && !display.isStartupActive() && !accessControl.isAccessGranted()) {
        accessControl.update();
    }
    
    // Kun håndter input hvis display er tændt og startup er færdig
    if (displayEnabled && !display.isStartupActive()) {
        char key = keypad.getKey();
        if (key) {
            if (!accessControl.isAccessGranted()) {
                // Håndter adgangskode input
                accessControl.handleInput(key);
                // Tjek om adgang lige er blevet givet
                if (accessControl.isAccessGranted()) {
                    lockSys.getCodeDisplay().turnOn();  // Tænd CodeDisplay når adgang givet
                    form.show();  // Skift til hovedsystem
                }
            } else {
                // Normal form input når adgang er givet
                form.handleInput(key);
            }
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
        // Tænd kun LCD display med startup sekvens
        displayEnabled = true;
        display.turnOn();  // Starter startup sekvens
        // CodeDisplay tændes først når adgangskode er korrekt
    } else if (!keyPressed && displayEnabled) {
        // Sluk begge displays og nulstil adgangskontrol
        displayEnabled = false;
        display.clear();
        lockSys.getCodeDisplay().turnOff();
        accessControl.begin();  // Nulstil adgangskontrol
    }
}