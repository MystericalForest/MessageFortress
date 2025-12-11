#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

class DisplayManager {
public:
  enum DisplayState {
    OFF,      // Slukket - ingen backlight
    STARTUP,  // Startup animation kører
    ON        // Tændt - normal drift
  };
  
private:
  LiquidCrystal_I2C lcd;
  DisplayState _state;
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
  void setState(DisplayState newState);
  DisplayState getState();
  void updateStartup();
};

#endif
