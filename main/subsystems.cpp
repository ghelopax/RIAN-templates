#include "subsystems.h"

// #########################
// DRIVETRAIN: Mecanum Drive
// #########################
MecanumDrivetrain MecanumDrivetrain::INSTANCE;
MecanumDrivetrain::MecanumDrivetrain()
  : leftfront(LF_A, LF_B),
    leftback(LB_A, LB_B),
    rightfront(RF_A, RF_B, true),
    rightback(RB_A, RB_B, true) {}

// default to forward movement
void MecanumDrivetrain::test() {
  leftfront .relControl(SPD_DRIVE_LF);
  leftback  .relControl(SPD_DRIVE_LB);
  rightfront.relControl(SPD_DRIVE_RF);
  rightback .relControl(SPD_DRIVE_RB);
}

void MecanumDrivetrain::update(uint8_t stra, uint8_t forw, uint8_t rota) {
  int16_t x = map(stra, 0, 255, -SPD_MAX,  SPD_MAX);
  int16_t y = map(forw, 0, 255,  SPD_MAX, -SPD_MAX);
  int16_t r = map(rota, 0, 255,  SPD_MAX, -SPD_MAX);
  int16_t d = max(abs(x) + abs(y) + abs(r), SPD_MAX);

  int16_t lf = (int32_t)( x + y - r) * SPD_DRIVE_LF / d;
  int16_t lb = (int32_t)(-x + y - r) * SPD_DRIVE_LB / d;
  int16_t rf = (int32_t)(-x + y + r) * SPD_DRIVE_RF / d;
  int16_t rb = (int32_t)( x + y + r) * SPD_DRIVE_RB / d;

  leftfront .control(lf);
  leftback  .control(lb);
  rightfront.control(rf);
  rightback .control(rb);

  #ifdef DEBUG_MECANUM
  Serial.println("MECANUM:");
  Serial.println(x);
  Serial.println(y);
  Serial.println(r);
  Serial.println(d);
  Serial.print(lf); SPC; Serial.println(rf);
  Serial.print(lb); SPC; Serial.println(rb);
  delay(500);
  #endif
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