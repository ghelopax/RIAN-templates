#pragma once

#include "hardware.h"

struct MecanumDrivetrain {
private:
  DCMotor leftfront, rightback, leftback, rightfront;

public:
  static MecanumDrivetrain INSTANCE;
  MecanumDrivetrain();
  void test(float rel_speed = 1.0);
  void update(uint8_t stra, uint8_t forw, uint8_t rota);
};

struct Intake {
private:
  bool state;
  DCMotor in;

public:
  static Intake INSTANCE;
  Intake();
  void update(bool togg);
};