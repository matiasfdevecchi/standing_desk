#ifndef Position_h
#define Position_h

#include "Arduino.h"

typedef struct PositionParams {
    uint8_t trigPin;
    uint8_t echoPin;
} position_params_t;

class Position {
  public:
    Position(position_params_t params);
    float getHeightInCentimeters();

  private:
    uint8_t _trigPin;
    uint8_t _echoPin;
};

#endif
