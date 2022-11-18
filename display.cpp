#include "display.h"

Display::Display() {
  _display = new LiquidCrystal_I2C(0x27, 16, 4);
  _display->init(); 
  _display->backlight();
}

void Display::setCurrentPosition(uint8_t v) {
  Serial.print("Display: current position ");
  Serial.println(v);
  _display->home();
  _display->print("Position: ");
  _display->setCursor(10, 0);
  _display->print("   ");
  _display->setCursor(10, 0);
  _display->print(v);
}

void Display::setCommand(String v) {
  _display->setCursor(0,1);
  _display->print("                ");
  _display->setCursor(0,1);
  _display->print(v);
}

void Display::clear() {
  _display->clear();
}
