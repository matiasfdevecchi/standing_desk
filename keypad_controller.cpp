#include "keypad_controller.h"
#include <keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'X','0','E', 'D'}
};

byte rowPins[ROWS] = { 6, 7, 8, 9 };
byte colPins[COLS] = { 5, 4, 3, 2 }; 

KeypadController::KeypadController() {
  _keypad = new Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
}

char KeypadController::getKey() {
  return _keypad->getKey();
}
