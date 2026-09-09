#include "subsystems.h"

// #########################
// DRIVETRAIN: Mecanum Drive
// #########################
MecanumDrivetrain MecanumDrivetrain::INSTANCE;
MecanumDrivetrain::MecanumDrivetrain()
  : leftfront(LF_A, LF_B),
    rightback(RB_A, RB_B, true),
    leftback(LB_A, LB_B),
    rightfront(RF_A, RF_B, true) {}

// default to forward movement
void MecanumDrivetrain::test(float rel_speed) {
  leftfront .relControl(rel_speed * CAL_DRIVE_LF);
  rightback .relControl(rel_speed * CAL_DRIVE_RB);
  leftback  .relControl(rel_speed * CAL_DRIVE_LB);
  rightfront.relControl(rel_speed * CAL_DRIVE_RF);
}

void MecanumDrivetrain::update(uint8_t stra, uint8_t forw, uint8_t rota) {
  float x = fMAP(stra, 0, 255, -1.0, 1.0);
  float y = fMAP(forw, 0, 255, 1.0, -1.0);
  float r = fMAP(rota, 0, 255, 1.0, -1.0);
  float d = max(abs(x) + abs(y) + abs(r), 1.0);

  float lf = (+x +y -r) / d;
  float rb = (+x +y +r) / d;
  float lb = (-x +y -r) / d;
  float rf = (-x +y +r) / d;

  leftfront .relControl(lf * CAL_DRIVE_LF);
  rightback .relControl(rb * CAL_DRIVE_RB);
  leftback  .relControl(lb * CAL_DRIVE_LB);
  rightfront.relControl(rf * CAL_DRIVE_RF);
}

// ##########
// SUBSYSTEMS
// ##########
Intake Intake::INSTANCE;
Intake::Intake() : state(false), in(IT_A, IT_B) {}

void Intake::update(bool togg) {
  state ^= togg;
  in.control((state ? SPD_INTAKE : 0));
}