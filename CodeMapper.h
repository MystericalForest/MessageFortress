#ifndef CODEMAPPER_H
#define CODEMAPPER_H

#include <Arduino.h>

/**
 * CodeMapper klasse
 * Konverterer button input til krypterings koder
 */
class CodeMapper {
public:
    CodeMapper();
    int getCode(int input);
    bool isValidInput(int input);
};

#endif