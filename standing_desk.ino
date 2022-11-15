#include "standing_desk.h"

StandingDesk* standingDesk;

void setup() {
  Serial.begin(9600);
  Serial.println("Standing Desk");

  uint8_t dir[1] = { 11 };
  uint8_t power[0] = {};
  engines_controller_params_t enginesControllerParams = { dir, 1, power, 0 };
  
  position_params_t positionParams = {
    trigPin: 12,
    echoPin: 13
  };
  
  standing_desk_params_t params = {
    minPosition: 74,
    maxPosition: 115,
    recordedPositionQuantity: 4,
    enginesControllerParams: enginesControllerParams,
    positionParams: positionParams,
  };
  
  standingDesk = new StandingDesk(params);
}

void loop() {
  standingDesk->loop();
}
