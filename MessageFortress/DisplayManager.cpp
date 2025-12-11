#include "DisplayManager.h"

DisplayManager::DisplayManager() : lcd(0x27, 16, 2), _state(OFF), _startupCount(0), _lastStartupTime(0) {}

void DisplayManager::begin() {
  lcd.init();
  setState(OFF);
}

void DisplayManager::showLines(String line1, String line2, int selectedIndex) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
  lcd.setCursor(15, selectedIndex);
  lcd.print(">");
}

void DisplayManager::showQuestion(const String &question) {
  lcd.clear();
  String q = question;
  if (q.length() > 16) q = q.substring(0, 16);
  lcd.setCursor(0, 0);
  lcd.print(q);
  lcd.setCursor(0, 1);
}

void DisplayManager::printInput(const String &input) {
  lcd.setCursor(0, 1);
  lcd.print(input);
}

void DisplayManager::clearLastChar(int pos) {
  lcd.setCursor(pos, 1);
  lcd.print(" ");
  lcd.setCursor(pos, 1);
}

void DisplayManager::clear() {
  lcd.clear();
  lcd.noBacklight();
}

void DisplayManager::setState(DisplayState newState) {
  _state = newState;
  
  switch (_state) {
    case OFF:
      lcd.clear();
      lcd.noBacklight();
      break;
      
    case STARTUP:
      lcd.backlight();
      _startupCount = 0;
      _lastStartupTime = millis();
      lcd.clear();
      break;
      
    case ON:
      lcd.backlight();
      break;
  }
}

DisplayManager::DisplayState DisplayManager::getState() {
  return _state;
}

void DisplayManager::updateStartup() {
  unsigned long now = millis();
  if (now - _lastStartupTime >= 1000) {
    _startupCount++;
    if (_startupCount <= 10) {
      lcd.clear();
      lcd.setCursor(7, 0);
      lcd.print(_startupCount);
      _lastStartupTime = now;
    } else {
      setState(ON);  // Gå til ON efter startup så LCD er tændt
    }
  }
}
