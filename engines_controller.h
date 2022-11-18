#ifndef EnginesController_h
#define EnginesController_h

#include "Arduino.h"

enum Direction { DIRECTION_DEFAULT, DIRECTION_UP, DIRECTION_DOWN };

class EnginesController {
  public:
    EnginesController();
    void setDirection(Direction dir);
    void setPower(uint8_t power);

  private:
    uint8_t _directionPin;
    uint8_t _powerPin;
};

#endif
