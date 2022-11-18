#ifndef Display_h
#define Display_h

#include "Arduino.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

class Display {
  public:
    Display();
    void setCurrentPosition(uint8_t v);
    void setCommand(String v);
    void clear();

  private:
    LiquidCrystal_I2C* _display;
};

#endif
