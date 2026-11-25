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

/* Drivetrain: Mecanum Drive */
MecanumDrivetrain::MecanumDrivetrain(Adafruit_PWMServoDriver &pwm)
  : leftfront (pwm, LF_A, LF_B),
    rightback (pwm, RB_A, RB_B, true),
    leftback  (pwm, LB_A, LB_B),
    rightfront(pwm, RF_A, RF_B, true) {}

// default to forward movement
void MecanumDrivetrain::test(float rel_power) {
  leftfront .relControl(rel_power * CAL_DRIVE_LF);
  rightback .relControl(rel_power * CAL_DRIVE_RB);
  leftback  .relControl(rel_power * CAL_DRIVE_LB);
  rightfront.relControl(rel_power * CAL_DRIVE_RF);
}

void MecanumDrivetrain::update(uint8_t stra, uint8_t forw, uint8_t rota) {
  float x = fMAP(stra, 0, 255, -1.0,  1.0);
  float y = fMAP(forw, 0, 255,  1.0, -1.0);
  float r = fMAP(rota, 0, 255,  1.0, -1.0);
  float d = max(fabs(x) + fabs(y) + fabs(r), 1.0);
  
  float lf = (+x +y -r) / d;
  float rb = (+x +y +r) / d;
  float lb = (-x +y -r) / d;
  float rf = (-x +y +r) / d;

  leftfront .relControl(lf * CAL_DRIVE_LF);
  rightback .relControl(rb * CAL_DRIVE_RB);
  leftback  .relControl(lb * CAL_DRIVE_LB);
  rightfront.relControl(rf * CAL_DRIVE_RF);
}

/* Intake */
Intake::Intake(Adafruit_PWMServoDriver &pwm) : state(false), motor(pwm, IT_A, IT_B) {}

void Intake::update(bool togg) {
  state ^= togg;
  motor.relControl((state ? POW_INTAKE : 0));
}