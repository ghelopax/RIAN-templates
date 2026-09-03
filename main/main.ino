#include "subsystems.h"

PWMDriver pwmDriver;
PS2_Controller ps2c;

void setup() {
  Serial.begin(115200);  

  pwmDriver.init();
  ps2c.init();
}

void loop() {
  ps2c.ps2.read_gamepad();

  MecanumDrivetrain::INSTANCE.update(
    ps2c.ps2.Analog(PSS_LX),
    ps2c.ps2.Analog(PSS_LY),
    ps2c.ps2.Analog(PSS_RX)
  );

  Intake::INSTANCE.update(
    ps2c.ps2.ButtonPressed(PSB_L1)
  );
}
