#include "standing_desk.h"

StandingDesk* standingDesk;

void setup() {
  Serial.begin(9600);
  Serial.println("Standing Desk");

  position_params_t positionParams = {
    trigPin: 12,
    echoPin: 13
  };
  
  standing_desk_params_t params = {
    minPosition: 75,
    maxPosition: 100,
    recordedPositionQuantity: 4,
    positionParams: positionParams,
  };
  
  standingDesk = new StandingDesk(params);
}

void loop() {
  standingDesk->loop();
}
