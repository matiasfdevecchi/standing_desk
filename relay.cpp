#include "relay.h"

Relay::Relay(uint8_t pin) {
  _pin = pin;
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  _value = false;
}

void Relay::on() {
  _value = true;
  digitalWrite(_pin, HIGH); 
}

void Relay::off() {
  _value = false;
  digitalWrite(_pin, LOW); 
}
