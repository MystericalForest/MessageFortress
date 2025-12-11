#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

class DisplayManager {
private:
  LiquidCrystal_I2C lcd;
  bool _startupActive;
  int _startupCount;
  unsigned long _lastStartupTime;
public:
  DisplayManager();
  void begin();
  void showLines(String line1, String line2, int selectedIndex);
  void showQuestion(const String &question);
  void printInput(const String &input);
  void clearLastChar(int pos);
  void clear();
  void turnOn();
  void updateStartup();
  void startStartup();
  bool isStartupActive();
};

#endif
