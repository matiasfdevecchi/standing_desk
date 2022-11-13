#ifndef Relay_h
#define Relay_h

#include "Arduino.h"

class Relay {
  public:
    Relay(uint8_t pin);
    void on();
    void off();
  private:
    uint8_t _pin;
    bool _value;
};

#endif
