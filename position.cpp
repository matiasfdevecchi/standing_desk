#include "Position.h"

Position::Position(position_params_t params) {
  _trigPin = params.trigPin;
  _echoPin = params.echoPin;
  pinMode(_trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(_echoPin, INPUT); // Sets the echoPin as an INPUT
}

float Position::getHeightInCentimeters() {
   // Clears the trigPin condition
  digitalWrite(_trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(_echoPin, HIGH);
  // Calculating the distance
  return duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
}
