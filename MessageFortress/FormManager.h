#ifndef FORM_MANAGER_H
#define FORM_MANAGER_H

#include "DisplayManager.h"
#include "KeypadManager.h"
#include <Arduino.h>

class FormManager {
private:
  DisplayManager &display;
  KeypadManager &keypad;

  String lines[10];
  String questions[10];

  int selectedLine;
  int topLine;

  void editLine(int index);
public:
  FormManager(DisplayManager &disp, KeypadManager &keys);
  void show();
  void handleInput(char key);
};

#endif
