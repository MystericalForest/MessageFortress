/**
 * CodeMapper.cpp
 * Håndterer mapping fra button input til krypterings koder
 */

#include "CodeMapper.h"
#include "config.h"

/**
 * Konstruktør for CodeMapper
 */
CodeMapper::CodeMapper() {}

/**
 * Konverterer button input til krypterings kode
 * @param input Button kombination (0-255)
 * @return 4-cifret kode fra CODES array
 */
int CodeMapper::getCode(int input) {
  if (isValidInput(input)) {
    return CODES[input];
  }
  return 0000;  // Fejl tilstand
}

/**
 * Tjekker om input er gyldigt
 * @param input Button kombination
 * @return true hvis input er mellem 0-255
 */
bool CodeMapper::isValidInput(int input) {
  return (input >= 0 && input <= 255);
}