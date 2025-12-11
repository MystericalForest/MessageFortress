#include "DisplayManager.h"

DisplayManager::DisplayManager() : lcd(0x27, 16, 2) {}

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
