/**
 * AccessControl.cpp
 * Implementering af adgangskode funktionalitet
 */

#include "AccessControl.h"
#include "config.h"

/**
 * Konstruktør for AccessControl
 */
AccessControl::AccessControl(DisplayManager& disp, KeypadManager& key)
    : display(disp), keypad(key), currentInput(""), accessGranted(false), showingError(false), errorStartTime(0) {}

/**
 * Initialiser AccessControl
 */
void AccessControl::begin() {
    accessGranted = false;
    currentInput = "";
    showingError = false;
    showPrompt();
}

/**
 * Håndterer input fra keypad
 */
void AccessControl::handleInput(char key) {
    if (key == '*') {
        // Reset input
        currentInput = "";
        showPrompt();
    } else if (key == '#') {
        // Tjek adgangskode
        if (currentInput == String(ACCESS_CODE)) {
            accessGranted = true;
            display.showQuestion("Adgang godkendt");
        } else {
            currentInput = "";
            display.showQuestion("Forkert kode!");
            showingError = true;
            errorStartTime = millis();
        }
    } else if (key >= '0' && key <= '9') {
        // Tilføj ciffer
        if (currentInput.length() < 6) {
            currentInput += key;
            display.printInput(currentInput);
        }
    }
}

/**
 * Returnerer om adgang er givet
 */
bool AccessControl::isAccessGranted() {
    return accessGranted;
}

/**
 * Viser adgangskode prompt
 */
void AccessControl::update() {
    // Tjek om fejlbesked skal skjules
    if (showingError && (millis() - errorStartTime > 2000)) {
        showingError = false;
        showPrompt();
    }
}

void AccessControl::showPrompt() {
    display.showQuestion("Indtast kode:");
    display.printInput("");
}