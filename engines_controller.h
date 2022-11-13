#ifndef EnginesController_h
#define EnginesController_h

#include "Arduino.h"

enum Direction { DIRECTION_DEFAULT, DIRECTION_UP, DIRECTION_DOWN };

typedef struct EnginesControllerParams {
  uint8_t* directionPins;
  uint8_t directionPinsLength;
  uint8_t* powerPins;
  uint8_t powerPinsLength;
} engines_controller_params_t;

class EnginesController {
  public:
    EnginesController(engines_controller_params_t params);
    void setDirection(Direction dir);
    void setPower(uint8_t power);

  private:
    uint8_t* _directionPins;
    uint8_t _directionPinsLength;
    uint8_t* _powerPins;
    uint8_t _powerPinsLength;
};

#endif
