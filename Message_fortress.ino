/**
 * Message Fortress - Escaperoom Krypterings Device
 * 
 * Dette er hovedfilen for krypterings-devicen der bruges i escaperoom.
 * Systemet skifter mellem låst tilstand (røde LED'er) og kode tilstand (blå LED'er)
 * med pulserende fade effekter.
 */

#include "config.h"
#include "LockSystem.h"

// Initialiser LockSystem med alle pins fra config.h
LockSystem lockSys(
    CODE_LED_1_PIN, CODE_LED_2_PIN,     // Blå kode LED'er
    LOCK_LED_1_PIN, LOCK_LED_2_PIN,     // Røde låse LED'er
    STATUS_RED_PIN, STATUS_GREEN_PIN, CONNECTION_PIN,  // Status LED'er
    BUTTON_1_PIN, BUTTON_2_PIN, BUTTON_3_PIN, BUTTON_4_PIN, // Input knapper 1-4
    BUTTON_5_PIN, BUTTON_6_PIN, BUTTON_7_PIN, BUTTON_8_PIN, // Input knapper 5-8
    DISPLAY_CLK_PIN, DISPLAY_DIO_PIN    // 7-segment display
);

// Global tilstandsvariabler
bool isLocked = true;        // Start i låst tilstand
unsigned long lastSwitch = 0; // Tidspunkt for sidste skift

/**
 * Setup funktion - køres én gang ved opstart
 */
void setup() {
    lockSys.setLocked(isLocked);  // Sæt initial tilstand
}

/**
 * Hovedloop - køres kontinuerligt
 * Håndterer automatisk skift mellem låst og kode tilstand (kun når låst op)
 */
void loop() {
    lockSys.update();  // Opdater LED'er, display og status

    // Kun skift tilstand hvis systemet er låst op med adgangskode
    if (lockSys.isSystemUnlocked()) {
        // Automatisk skift mellem låst og kodevisning hver SWITCH_DELAY ms
        unsigned long now = millis();
        if (now - lastSwitch > SWITCH_DELAY) {
            isLocked = !isLocked;              // Skift tilstand
            lockSys.setLocked(isLocked);       // Opdater system
            lastSwitch = now;                  // Gem tidspunkt
        }
    }
}
