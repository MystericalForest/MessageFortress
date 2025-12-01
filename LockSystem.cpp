#include "LockSystem.h"
#include "config.h"
#include <Arduino.h>

/**
 * Konstruktør for LockSystem
 * Initialiserer alle komponenter og sætter standard værdier
 */
LockSystem::LockSystem(int c1, int c2, int l1, int l2, int redPin, int greenPin, int connPin, int btn1, int btn2, int btn3, int btn4, int btn5, int btn6, int btn7, int btn8, int clk, int dio)
    : codeLED1(c1), codeLED2(c2), lockLED1(l1), lockLED2(l2),  // LED objekter
      status(redPin, greenPin, connPin),                        // Status LED system
      display(btn1, btn2, btn3, btn4, btn5, btn6, btn7, btn8, clk, dio), // Kode display system (8 knapper)
      locked(true), lastUpdate(0), fadeDelay(FADE_DELAY),      // Timing variabler
      brightness1((BRIGHTNESS_MIN + BRIGHTNESS_MAX) / 2), brightness2(BRIGHTNESS_MAX),  // Start brightness
      fadeStep(FADE_STEP), direction(1) {                      // Fade indstillinger
        connected = false;  // Start som ikke forbundet
        status.begin();     // Initialiser status system
        display.begin();    // Initialiser display system
      }

/**
 * Sætter låse tilstanden for systemet
 * @param state true = låst, false = ulåst
 */
void LockSystem::setLocked(bool state) {
    locked = state;           // Gem intern tilstand
    status.setLocked(state);  // Opdater status LED'er
}

/**
 * Returnerer om systemet er låst op med adgangskode
 */
bool LockSystem::isSystemUnlocked() {
    return display.isUnlocked();
}

/**
 * Hovedloop funktion - kaldes kontinuerligt
 * Håndterer LED fade effekter og opdaterer alle subsystemer
 */
void LockSystem::update() {
    unsigned long now = millis();

    // Opdater subsystemer
    status.update();   // Status LED'er og forbindelse
    display.update();  // Kode display og knapper

    // LED fade timing - kun opdater når der er gået nok tid
    if (now - lastUpdate > fadeDelay) {
        lastUpdate = now;

        // Opdater lysstyrker - skaber "pulserende" effekt
        brightness1 += fadeStep * direction;  // LED 1 stiger/falder
        brightness2 -= fadeStep * direction;  // LED 2 falder/stiger (modsat)

        // Tjek grænser og skift retning når vi når min/max
        if (brightness1 >= BRIGHTNESS_MAX || brightness1 <= BRIGHTNESS_MIN) {
            direction *= -1;  // Skift fade retning
        }
    }

    // Anvend PWM-værdier på de aktive LED’er
    // Tjek om systemet er låst op med adgangskode
    bool systemUnlocked = display.isUnlocked();
    
    if (!systemUnlocked) {
        // Adgangskode tilstand: Konstant rød LED
        lockLED1.setBrightness(255);
        lockLED2.setBrightness(255);
        codeLED1.setBrightness(0);
        codeLED2.setBrightness(0);
    } else if (locked) {
        // Låst tilstand: Pulserende røde LED'er
        lockLED1.setBrightness(brightness1);
        lockLED2.setBrightness(brightness2);
        codeLED1.setBrightness(0);
        codeLED2.setBrightness(0);
    } else {
        // Kode tilstand: Pulserende blå LED'er
        codeLED1.setBrightness(brightness1);
        codeLED2.setBrightness(brightness2);
        lockLED1.setBrightness(0);
        lockLED2.setBrightness(0);
    }
}
