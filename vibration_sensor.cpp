#include "vibration_sensor.h"

VibrationSensor::VibrationSensor(uint8_t pin) {
  _pin = pin;
  pinMode(_pin, INPUT);
}

bool VibrationSensor::isActive() {
  return digitalRead(_pin) == HIGH;
}
