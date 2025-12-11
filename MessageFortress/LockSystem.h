#ifndef LOCKSYSTEM_H
#define LOCKSYSTEM_H

#include "LED.h"
#include "Box_Status.h"
#include "CodeDisplay.h"

class FormManager;

class LockSystem {
private:
    LED codeLED1;
    LED codeLED2;
    LED lockLED1;
    LED lockLED2;
    Box_Status status;
    CodeDisplay display;
    bool locked;
    bool key_switch;
    bool connected;
    unsigned long lastUpdate;
    int fadeDelay;
    int brightness1;
    int brightness2;
    int fadeStep;
    int direction; // 1 = stigende, -1 = faldende
    int keyPin;
    FormManager* formManager;
public:
    LockSystem(int c1, int c2, int l1, int l2, int redPin, int greenPin,  int keyPin, int connPin, int btn1, int btn2, int btn3, int btn4, int btn5, int btn6, int btn7, int btn8, int clk, int dio);
    void setFormManager(FormManager* fm);
    void setLocked(bool state);
    void update();
    CodeDisplay& getCodeDisplay();
    bool isUnlocked();
    void setDisplayEnabled(bool enabled);
};

#endif
