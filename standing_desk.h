#ifndef StandingDesk_h
#define StandingDesk_h

#include "Arduino.h"
#include "position.h"
#include "display.h"
#include "engines_controller.h"
#include "keypad_controller.h"

typedef struct StandingDeskParams {
  uint8_t minPosition;
  uint8_t maxPosition;
  uint8_t recordedPositionQuantity;
  engines_controller_params_t enginesControllerParams;
  position_params_t positionParams;
} standing_desk_params_t;

class StandingDesk {
  public:
    StandingDesk(standing_desk_params_t params);
    void loop();
  private:
    uint8_t _minPosition;
    uint8_t _maxPosition;
    uint8_t _recordedPositionQuantity;
    uint8_t _desiredPosition;
    bool _moving;
    String _digits;

    KeypadController* _keypadController;
    EnginesController* _enginesController;
    Position* _position;
    Display* _display;
    
    void setPosition(uint8_t newPosition);
    void setRecordedPosition(uint8_t number);
    void recordPosition(uint8_t number, uint8_t position);
    void deleteRecordedPosition(uint8_t number);
    void move(float currentPosition);
    void cancelMovement();
    void analyzeKey(char key);
    void setMotorsDirection(float actualPosition, uint8_t desiredPosition);
    void setDefaultDirection();
    uint8_t getMotorsPower(float actualPosition, uint8_t desiredPosition);
    void moveMotors(uint8_t power);
    void stopMotors();
    void validateCollisions();
};

#endif
