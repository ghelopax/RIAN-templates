#include "subsystems.h"

void setup() {
  Serial.begin(115200);  

  PWMDriver::INSTANCE.init();
  PS2_Controller::INSTANCE.init();
}

void loop() {
  gamepad().read_gamepad();

  MecanumDrivetrain::INSTANCE.update(
    gamepad().Analog(PSS_LX),
    gamepad().Analog(PSS_LY),
    gamepad().Analog(PSS_RX)
  );

  Intake::INSTANCE.update(
    gamepad().ButtonPressed(PSB_L1)
  );
}
