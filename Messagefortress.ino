/**
 * Message Fortress - Escaperoom Krypterings Device
 * Simpel .ino fil der kun initialiserer og kører hovedklassen
 */

#include "MessageFortress.h"

// Hovedsystem objekt
MessageFortress fortress;

void setup() {
    fortress.begin();
}

void loop() {
    fortress.update();
}
