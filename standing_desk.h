#ifndef StandingDesk_h
#define StandingDesk_h

#include "Arduino.h"
#include "relay.h"
#include "position.h"

class StandingDesk {
  public:
    StandingDesk(byte minPosition, byte maxPosition, byte recordedPositionQuantity, byte relayPin1, byte relayPin2, byte positionTriggerPin, byte positionEchoPin);
    void setPosition(byte newPosition);
    void setRecordedPosition(byte number);
    void recordPosition(byte number, byte position);
    void deleteRecordedPosition(byte number);
    void move();
  private:
    byte _minPosition;
    byte _maxPosition;
    byte _recordedPositionQuantity;
    byte _desiredPosition;
    bool _moving;
    byte _movingDirection; //0 - Quieto, 1 - Arriba, 2 - Abajo

    Relay* relay1;
    Relay* relay2;
    Position* position;
    
    void setMotorsDirection(byte actualPosition, byte desiredPosition);
    void setDefaultDirection();
    void moveMotors();
    void stopMotors();
    void validateCollisions();
};

#endif
