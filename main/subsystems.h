#pragma once

#include "hardware.h"

struct MecanumDrivetrain {
private:
  DCMotor leftfront, leftback, rightfront, rightback;

public:
  static MecanumDrivetrain INSTANCE;
  MecanumDrivetrain();
  void test();
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