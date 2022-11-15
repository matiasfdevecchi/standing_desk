#ifndef KeypadController_h
#define KeypadController_h

#include "Arduino.h"
#include <Keypad.h>

class KeypadController {
  public:
    KeypadController();
    char getKey();

  private:
    Keypad* _keypad;
};

#endif
