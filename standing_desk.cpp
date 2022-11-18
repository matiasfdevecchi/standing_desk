#include "standing_desk.h"
#include <EEPROM.h>
#include <math.h>

bool isBetween(uint8_t v, uint8_t min, uint8_t max);
void serialPrint(String msg1, uint8_t v1);
void serialPrint(String msg1, uint8_t v1, String msg2);
void serialPrint(String msg1, uint8_t v1, String msg2, uint8_t v2);
void serialPrint(String msg1, float v1, String msg2, uint8_t v2);
void serialPrint(String msg1, uint8_t v1, String msg2, uint8_t v2, String msg3);

StandingDesk::StandingDesk(standing_desk_params_t params) {
  //TODO: Crear y setear sensor vibracion
  _enginesController = new EnginesController();
  _position = new Position(params.positionParams);
  _keypadController = new KeypadController();
  _display = new Display();
  
  _minPosition = params.minPosition;
  _maxPosition = params.maxPosition;
  _recordedPositionQuantity = params.recordedPositionQuantity;
  
  _desiredPosition = _position->getHeightInCentimeters();
  _moving = false;
  _digits = "";
}

void StandingDesk::loop() {
  char key = _keypadController->getKey();
  if (key != NULL) {
    analyzeKey(key);
  }
  
  float currentPosition = _position->getHeightInCentimeters();
  serialPrint("Current position: ", currentPosition);
  _display->setCurrentPosition(currentPosition);
  move(currentPosition);
}

void StandingDesk::analyzeKey(char key) {
  if (key == 'X') {
    cancelMovement();
    _digits = "";
  } else if (key == 'A' || key == 'B' || key == 'C' || key == 'D') {
    uint8_t number = key - '@';
    if (_digits == "") {
      setRecordedPosition(number);
    } else {
      recordPosition(number, _digits.toInt());
    }
    _digits = "";
  } else if (key == 'E') {
    if (_digits != "") {
      setPosition(_digits.toInt());
      _digits = "";
    }
  } else {
    _digits += key;
    Serial.print("Digits: ");
    Serial.println(_digits);
  }
  _display->setCommand(_digits);
}

void StandingDesk::setPosition(uint8_t newPosition) {
  if (!isBetween(newPosition, _minPosition, _maxPosition)) {
    //TODO: Mostrar error en pantalla
    serialPrint("Position value", newPosition, "out of range");
    return;
  }
  serialPrint("Setting new position:", newPosition);
  _desiredPosition = newPosition;
  _moving = true;
}

void StandingDesk::setRecordedPosition(uint8_t number) {
  if (number < 1 && number > _recordedPositionQuantity) {
    //TODO: Mostrar error en pantalla
    serialPrint("Recorded position", number, "out of range");
    return;
  }
  
  uint8_t index = number - 1;
  uint8_t position = EEPROM.read(index);
  if (position == 0) {
    //TODO: Mostrar en pantalla que el dato no fue guardado
    serialPrint("Recorded position", number, "is empty");
    return; 
  }
  serialPrint("Set recorded position", number, ". Value:", position);
  setPosition(position);
}

void StandingDesk::recordPosition(uint8_t number, uint8_t position) {
  if (number < 1 && number > _recordedPositionQuantity) {
    //TODO: Mostrar error en pantalla
    serialPrint("Recorded position", number, "out of range");
    return;
  }

  if (!isBetween(position, _minPosition, _maxPosition)) {
    //TODO: Mostrar error en pantalla
    serialPrint("Record position value", position, "out of range");
    return;
  }

  serialPrint("Recording position", number, ". Value:", position);
  uint8_t index = number - 1;
  uint8_t existingValue = EEPROM.read(index);
  if (existingValue != position) {
    EEPROM.write(index, position);
  }
}

void StandingDesk::deleteRecordedPosition(uint8_t number) {
  if (number < 1 && number > _recordedPositionQuantity) {
    //TODO: Mostrar error en pantalla
    serialPrint("Deleted recorded position", number, "out of range");
    return;
  }
  uint8_t index = number - 1;
  uint8_t existingValue = EEPROM.read(index);
  if (existingValue != 0) {
    EEPROM.write(index, 0);
  }
}

void StandingDesk::move(float currentPosition) {
  if (!_moving) {
    _enginesController->setPower(0);
    return;
  }
  
  if (abs(_desiredPosition - currentPosition) < 0.5) {
    serialPrint("Position", _desiredPosition, "arrived");
    stopMotors();
    return;
  }

  serialPrint("Actual position", currentPosition, ". Desired position", _desiredPosition);
  setMotorsDirection(currentPosition, _desiredPosition);
  uint32_t power = getMotorsPower(currentPosition, _desiredPosition);
  moveMotors(power);
  validateCollisions();
}

void StandingDesk::cancelMovement() {
  Serial.println("Cancel movement");
  stopMotors();
}

void StandingDesk::setMotorsDirection(float actualPosition, uint8_t desiredPosition) {
  bool normalDirection = actualPosition <= desiredPosition;
  if (normalDirection) {
    Serial.println("Setting motors direction to UP");
    _enginesController->setDirection(DIRECTION_UP);
  } else {
    Serial.println("Setting motors direction to DOWN");
    _enginesController->setDirection(DIRECTION_DOWN);
  }
}

void StandingDesk::moveMotors(uint8_t power) {
  if (!_moving) {
    Serial.println("Se solicita mover motores, pero moving es false");
    //TODO: Mostrar error de seguridad en pantalla
    return;
  }
  serialPrint("Move motors, power", power);
  _enginesController->setPower(power);
}

void StandingDesk::stopMotors() {
  Serial.println("Stoping motors");
  _moving = false;
  _enginesController->setPower(0);
  _enginesController->setDirection(DIRECTION_DEFAULT);
}

void StandingDesk::validateCollisions() {
  bool existCollisions = false; //TODO: implementar con el sensor de vibracion
  if (existCollisions) {
    stopMotors();
  }
}

uint8_t StandingDesk::getMotorsPower(float actualPosition, uint8_t desiredPosition) {
  uint8_t breakPoint = 5;
  uint8_t diff = min(breakPoint, abs(desiredPosition - actualPosition));
  return map(diff, 0, breakPoint, 0, 255);
}

bool isBetween(uint8_t v, uint8_t min, uint8_t max) {
  return v >= min && v <= max;
}

void serialPrint(String msg1, uint8_t v1) {
  Serial.print(msg1);
  Serial.print(" ");
  Serial.println(v1);
}

void serialPrint(String msg1, uint8_t v1, String msg2) {
  Serial.print(msg1);
  Serial.print(" ");
  Serial.print(v1);
  Serial.print(" ");
  Serial.println(msg2);
}

void serialPrint(String msg1, uint8_t v1, String msg2, uint8_t v2) {
  Serial.print(msg1);
  Serial.print(" ");
  Serial.print(v1);
  Serial.print(" ");
  Serial.print(msg2);
  Serial.print(" ");
  Serial.println(v2);
}

void serialPrint(String msg1, float v1, String msg2, uint8_t v2) {
  Serial.print(msg1);
  Serial.print(" ");
  Serial.print(v1);
  Serial.print(" ");
  Serial.print(msg2);
  Serial.print(" ");
  Serial.println(v2);
}

void serialPrint(String msg1, uint8_t v1, String msg2, uint8_t v2, String msg3) {
  Serial.print(msg1);
  Serial.print(" ");
  Serial.print(v1);
  Serial.print(" ");
  Serial.print(msg2);
  Serial.print(" ");
  Serial.print(v2);
  Serial.print(" ");
  Serial.println(msg3);
}
