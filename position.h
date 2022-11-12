#ifndef Position_h
#define Position_h

#include "Arduino.h"

class Position {
  public:
    Position(int trigPin, int echoPin);
    float getHeightInCentimeters();

  private:
    int _trigPin;
    int _echoPin;
};

#endif
