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

#include "config.h"

struct PWMDriver {
  Adafruit_PWMServoDriver pwm;
  PWMDriver();
  bool init();
};

struct PS2_Controller {
  PS2X ps2;
  void init();
};

struct DCMotor {
private:
  Adafruit_PWMServoDriver &pwm;
  uint8_t channelA, channelB;
  bool reverse;

public:
  DCMotor(Adafruit_PWMServoDriver &_pwm, uint8_t _channelA, uint8_t _channelB, bool _reverse = false);
  void control(int16_t power);
  void relControl(float rel_power);
};

struct Servo {
private:
  Adafruit_PWMServoDriver &pwm;
  uint8_t channel;

public:
  Servo(Adafruit_PWMServoDriver &_pwm, uint8_t _channel);
  void control(int16_t position);
  void relControl(float rel_pos);
};

struct CRServo {
private:
  Adafruit_PWMServoDriver &pwm;
  uint8_t channel;

public:
  CRServo(Adafruit_PWMServoDriver &_pwm, uint8_t _channel);
  void control(int16_t speed);
  void relControl(float rel_speed);
};