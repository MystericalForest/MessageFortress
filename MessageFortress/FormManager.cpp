#include "FormManager.h"

FormManager::FormManager(DisplayManager &disp, KeypadManager &keys)
  : display(disp), keypad(keys), selectedLine(0), topLine(0)
{
  // Init svar
  String initLines[10] = {
    "Svar 1", "Svar 2", "Svar 3", "Svar 4", "Svar 5",
    "Svar 6", "Svar 7", "Svar 8", "Svar 9", "Svar 10"
  };
  for (int i = 0; i < 10; i++) lines[i] = initLines[i];

  // Init spørgsmål
  String initQuestions[10] = {
    "Hvor mange timer?",
    "Hvor mange stk?",
    "Angiv temp (C)?",
    "Indtast ID-nummer:",
    "Hvor mange fejl?",
    "Antal tests?",
    "Hvor mange km?",
    "Hvor mange dage?",
    "Indtast kode:",
    "Hvor meget volt?"
  };
  for (int i = 0; i < 10; i++) questions[i] = initQuestions[i];
}

void FormManager::show() {
  int indexInWindow = selectedLine - topLine;
  display.showLines(lines[topLine], lines[topLine + 1], indexInWindow);
}

void FormManager::editLine(int index) {
  display.showQuestion(questions[index]);
  String input = "";

  while (true) {
    char key = keypad.getKey();
    if (key) {
      if (key == '#') {       // Gem
        lines[index] = input;
        break;
      } else if (key == 'D') { // Fortryd
        break;
      } else if (isdigit(key)) {
        if (input.length() < 16) {
          input += key;
          display.printInput(input);
        }
      } else if (key == '*') {
        if (input.length() > 0) {
          input.remove(input.length() - 1);
          display.clearLastChar(input.length());
        }
      }
    }
  }
  show();
}

void FormManager::handleInput(char key) {
  switch (key) {
    case 'A': // op
      if (selectedLine > 0) {
        selectedLine--;
        if (selectedLine < topLine) topLine--;
        show();
      }
      break;
    case 'B': // ned
      if (selectedLine < 9) {
        selectedLine++;
        if (selectedLine > topLine + 1 && topLine < 8) topLine++;
        show();
      }
      break;
    case 'C': // rediger
      editLine(selectedLine);
      break;
    default:
      break;
  }
}
