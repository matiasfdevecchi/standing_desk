#ifndef VibrationSensor_h
#define VibrationSensor_h

#include "Arduino.h"

class VibrationSensor {
  public:
    VibrationSensor(uint8_t pin);
    bool isActive();
  private:
    uint8_t _pin;
};

#endif
