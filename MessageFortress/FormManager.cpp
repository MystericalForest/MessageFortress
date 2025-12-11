#include "FormManager.h"

FormManager::FormManager(DisplayManager &disp, KeypadManager &keys)
  : display(disp), keypad(keys), selectedLine(0), topLine(0)
{
  // Init koder
  String initLines[10] = {
    "Kode 1", "Kode 2", "Kode 3", "Kode 4", "Kode 5",
    "Kode 6", "Kode 7", "Kode 8", "Kode 9", "Kode 10"
  };
  for (int i = 0; i < 10; i++) lines[i] = initLines[i];

  // Init korrekte svar
  correctAnswers[0] = "24";
  correctAnswers[1] = "156";
  correctAnswers[2] = "37";
  correctAnswers[3] = "9842";
  correctAnswers[4] = "3";
  correctAnswers[5] = "12";
  correctAnswers[6] = "450";
  correctAnswers[7] = "7";
  correctAnswers[8] = "1337";
  correctAnswers[9] = "220";

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
        if (input == correctAnswers[index]) {
          lines[index] = "Kode " + String(index + 1) + " " + input + " ✓";
        } else {
          lines[index] = "Kode " + String(index + 1) + " " + input;
        }
        break;
      } else if (key == 'D') { // Fortryd
        break;
      } else if (isdigit(key)) {
        if (input.length() < 10) {
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
