#include "engines_controller.h"

EnginesController::EnginesController(engines_controller_params_t params) {
  _directionPins = params.directionPins;
  _directionPinsLength = params.directionPinsLength;
  _powerPins = params.powerPins;
  _powerPinsLength = params.powerPinsLength;

  for (uint8_t i = 0; i < _directionPinsLength; i++)
    pinMode(_directionPins[i], OUTPUT);
  setDirection(DIRECTION_DEFAULT);
    
  for (uint8_t i = 0; i < _powerPinsLength; i++)
    pinMode(_powerPins[i], OUTPUT);
  setPower(0);
  
}

void EnginesController::setDirection(Direction dir) {
  uint8_t value = LOW;
  if (dir == DIRECTION_DOWN)
    value = HIGH;

  for (uint8_t i = 0; i < _directionPinsLength; i++)
    digitalWrite(_directionPins[i], value);
  
}

void EnginesController::setPower(uint8_t power) {
  //Para rele. Cambiar para transistor
  uint8_t value = LOW;
  if (power > 100)
    value = HIGH;

  for (byte i = 0; i < _powerPinsLength; i++)
    digitalWrite(_powerPins[i], value);
}
