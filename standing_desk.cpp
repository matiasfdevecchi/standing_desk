#include "standing_desk.h"
#include <EEPROM.h>

bool isBetween(byte v, byte min, byte max);

StandingDesk::StandingDesk(byte minPosition, byte maxPosition, byte recordedPositionQuantity, byte relayPin1, byte relayPin2, byte positionTriggerPin, byte positionEchoPin) {
  //TODO: Crear y setear sensor vibracion
  relay1 = new Relay(relayPin1);
  relay2 = new Relay(relayPin2);
  position = new Position(positionTriggerPin, positionEchoPin);
  
  _minPosition = minPosition;
  _maxPosition = maxPosition;
  _recordedPositionQuantity = recordedPositionQuantity;
  
  _desiredPosition = position->getHeightInCentimeters();
  _moving = false;
  _movingDirection = 0;
}

void StandingDesk::setPosition(byte newPosition) {
  if (!isBetween(newPosition, _minPosition, _maxPosition)) {
    //TODO: Mostrar error en pantalla
    return;
  }
  _desiredPosition = newPosition;
  _moving = true;
}

void StandingDesk::setRecordedPosition(byte number) {
  if (number < 1 && number > _recordedPositionQuantity) {
    //TODO: Mostrar error en pantalla
    return;
  }
  
  byte index = number - 1;
  byte position = EEPROM.read(index);
  if (position == 0) {
    //TODO: Mostrar en pantalla que el dato no fue guardado
    return; 
  }

  setPosition(position);
}

void StandingDesk::recordPosition(byte number, byte position) {
  if (number < 1 && number > _recordedPositionQuantity) {
    //TODO: Mostrar error en pantalla
    return;
  }

  if (!isBetween(position, _minPosition, _maxPosition)) {
    //TODO: Mostrar error en pantalla
    return;
  }

  byte index = number - 1;
  byte existingValue = EEPROM.read(index);
  if (existingValue != position) {
    EEPROM.write(index, position);
  }
}

void StandingDesk::deleteRecordedPosition(byte number) {
  if (number < 1 && number > _recordedPositionQuantity) {
    //TODO: Mostrar error en pantalla
    return;
  }
  byte index = number - 1;
  byte existingValue = EEPROM.read(index);
  if (existingValue != 0) {
    EEPROM.write(index, 0);
  }
}

void StandingDesk::move() {
  if (!_moving) return;
  
  int actualPosition = position->getHeightInCentimeters();
  if (_desiredPosition == actualPosition) {
    stopMotors();
    return;
  }

  setMotorsDirection(actualPosition, _desiredPosition);
  moveMotors();
  validateCollisions();
}

void StandingDesk::cancelMovement() {
  stopMotors();
}

void StandingDesk::setMotorsDirection(byte actualPosition, byte desiredPosition) {
  bool normalDirection = actualPosition <= desiredPosition;
  if (normalDirection) {
    _movingDirection = 1;
    //TODO: Preparar motores para giro normal hacia arriba
  } else {
    _movingDirection = 2;
    //TODO: Preparar motores para giro invertido hacia abajo
  }
}

void StandingDesk::setDefaultDirection() {
  //TODO: Setear posicion de reposo
}

void StandingDesk::moveMotors() {
  if (!_moving) {
    Serial.println("Se solicita mover motores, pero moving es false");
    return;
  }
  //TODO: mover motores
}

void StandingDesk::stopMotors() {
  _moving = false;
  _movingDirection = 0;
  //TODO: Parar motores
}

void StandingDesk::validateCollisions() {
  bool existCollisions = false; //TODO: implementar con el sensor de vibracion
  if (existCollisions) {
    stopMotors();
  }
}

bool isBetween(byte v, byte min, byte max) {
  return v >= min && v <= max;
}
