#include "display.h"

Display::Display() {
  _display = new LiquidCrystal_I2C(0x27, 16, 4);
  _display->init(); 
  _display->backlight();
}

void Display::setCurrentPosition(uint8_t v) {
  Serial.println(sprintf("Display: current position %u", v));
  _display->home();
  _display->print(sprintf("Posicion: %u", v));
}

void Display::setCommand(const char* v) {
  _display->setCursor(0,1);
  _display->print(v);
}

void Display::clear() {
  _display->clear();
}
