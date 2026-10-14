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

#include "hardware.h"

struct MecanumDrivetrain {
private:
  DCMotor leftfront, rightback, leftback, rightfront;

public:
  MecanumDrivetrain(Adafruit_PWMServoDriver &pwm);
  void test(float rel_power = 1.0);
  void update(uint8_t stra, uint8_t forw, uint8_t rota);
};

struct Intake {
private:
  bool state;
  DCMotor motor;

public:
  Intake(Adafruit_PWMServoDriver &pwm);
  void update(bool togg);
};