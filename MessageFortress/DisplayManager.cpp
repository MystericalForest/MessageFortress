#include "DisplayManager.h"

DisplayManager::DisplayManager() : lcd(0x27, 16, 2), _startupActive(false), _startupCount(0), _lastStartupTime(0) {}

void DisplayManager::begin() {
  lcd.init();
  lcd.backlight();
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

void DisplayManager::turnOn() {
  lcd.backlight();
  startStartup();
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
      _startupActive = false;
    }
  }
}

void DisplayManager::startStartup() {
  _startupActive = true;
  _startupCount = 0;
  _lastStartupTime = millis();
  lcd.clear();
  lcd.setCursor(7, 0);
  lcd.print("1");
  _startupCount = 1;
}

bool DisplayManager::isStartupActive() {
  return _startupActive;
}
