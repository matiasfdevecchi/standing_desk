#ifndef Position_h
#define Position_h

#include "Arduino.h"

class Position {
  public:
    Position(int trigPin, int echoPin);
    int getValue();

  private:
    int _trigPin;
    int _echoPin;
};

#endif
