#include "engines_controller.h"

EnginesController::EnginesController() {
  _directionPin = 11;
  _powerPin = 10;

  pinMode(_directionPin, OUTPUT);
  setDirection(DIRECTION_DEFAULT);
    
  pinMode(_powerPin, OUTPUT);
  setPower(0);
  
}

void EnginesController::setDirection(Direction dir) {
  uint8_t value = LOW;
  if (dir == DIRECTION_UP)
    value = HIGH;

  digitalWrite(_directionPin, value);
  
}

void EnginesController::setPower(uint8_t power) {
  /*uint8_t value = HIGH;
  if (power != 0)
    value = LOW;
    
  Serial.print("Engines controller: move ");
  Serial.println(value);
  //Para rele
  /* uint8_t value = LOW;
  if (power > 100)
    value = HIGH;

  for (byte i = 0; i < _powerPinsLength; i++)
    digitalWrite(_powerPins[i], value);
  

  //Para transistor
  Serial.print("Power pin: ");
  Serial.println(_powerPin);
  digitalWrite(_powerPin, value);*/
  uint8_t value = 255 - power;
  analogWrite(_powerPin, value);
}
