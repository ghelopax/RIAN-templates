/*
 /\_/\  /\_/\  /\_/\  /\_/\
( o.o )( o.o )( o.o )( o.o )
 > ^ <  > ^ <  > ^ <  > ^ <
 /\_/\                /\_/\
( o.o )   ghelopax   ( o.o )
 > ^ <                > ^ <
 /\_/\  /\_/\  /\_/\  /\_/\
( o.o )( o.o )( o.o )( o.o )
 > ^ <  > ^ <  > ^ <  > ^ <
*/

#include "mechanism.h"

PWMDriver pwm_driver;
Adafruit_PWMServoDriver &pwm = pwm_driver.pwm;
PS2_Controller ps2_controller;
PS2X &gamepad = ps2_controller.ps2;

struct Robot {
  private:
  MecanumDrivetrain drivetrain = MecanumDrivetrain(pwm);
  Intake intake = Intake(pwm);

  public:
  void periodic() {
    drivetrain.update(
      gamepad.Analog(PSS_LX), 
      gamepad.Analog(PSS_LY), 
      gamepad.Analog(PSS_RX)
    );

    intake.update(
      gamepad.ButtonPressed(PSB_L1)
    );
  }
} robot;

void setup() {
  Serial.begin(115200);
  pwm_driver.init();
  ps2_controller.init();
}

void loop() {
  gamepad.read_gamepad();
  robot.periodic();
}
