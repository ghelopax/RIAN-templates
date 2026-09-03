#pragma once

#include "config.h"

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <PS2X_lib.h>

struct PWMDriver {
  static Adafruit_PWMServoDriver pwm;
  PWMDriver();
  void init();
};

struct PS2_Controller {
  PS2X ps2;
  void init();
};

struct DCMotor {
private:
  uint8_t channelA, channelB;
  bool reverse;

public:
  DCMotor(uint8_t _channelA, uint8_t _channelB, bool _reverse = false);
  void control(int16_t speed);
  void relControl(float rel_speed);
};

struct Servo {
private:
  uint8_t channel;

public:
  Servo(uint8_t _channel);
  void control(int16_t position);
  void relControl(float rel_pos);
};

struct CRServo {
private:
  uint8_t channel;

public:
  CRServo(uint8_t _channel);
  void control(int16_t speed);
  void relControl(float rel_speed);
};