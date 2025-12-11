#include "KeypadManager.h"

KeypadManager::KeypadManager()
  : keys{{'1','2','3','A'},
         {'4','5','6','B'},
         {'7','8','9','C'},
         {'*','0','#','D'}},
    colPins{26, 27, 28, 29},
    rowPins{30, 31, 32, 33},
    keypad(makeKeymap(keys), rowPins, colPins, 4, 4)
{}

char KeypadManager::getKey() {
  return keypad.getKey();
}
