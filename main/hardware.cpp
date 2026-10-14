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

/* PWM Driver: 12-bit */
PWMDriver::PWMDriver() { pwm = Adafruit_PWMServoDriver(); }
bool PWMDriver::init() {
  Serial.print(F("Initializing PCA9685..."));

  // PWM Init
  if (!pwm.begin()) return Serial.print(F("failed.")), false;
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(50);
  // Wire Init
  Wire.setClock(400000);

  return Serial.print(F("done.")), true;
}

/* PS2 Controller */
void PS2_Controller::init() {
  Serial.println(F("Initializing PS2 controller..."));

  uint8_t error = ps2.config_gamepad(PS2_CLK, PS2_CMD, PS2_ATT, PS2_DAT);
  while (error != 0) {
    switch (error) {
      case 1:
        Serial.println("Error code 1: No controller found, check wiring.");
        break;
      case 2:
        Serial.println("Error code 2: Controller found but not accepting commands.");
        break;
      case 3:
        Serial.println("Error code 3: Controller refusing to enter Pressures mode, may not support it.");
        break;
    }

    delay(1000);

    error = ps2.config_gamepad(PS2_CLK, PS2_CMD, PS2_ATT, PS2_DAT);
  }

  Serial.println(F("done."));
}

/* DC Motor */
DCMotor::DCMotor(Adafruit_PWMServoDriver &_pwm, uint8_t _channelA, uint8_t _channelB, bool _reverse)
  : pwm(_pwm),
    channelA(_channelA),
    channelB(_channelB),
    reverse(_reverse) {}

void DCMotor::control(int16_t power) {
  if (abs(power) < RAW_POW_DEAD) power = 0;
  if (reverse) power = -power;

  pwm.setPWM(channelA, 0, ((power > 0) ? power : 0));
  pwm.setPWM(channelB, 0, ((power < 0) ? (-power) : 0));
}

// rel_speed = R[-1...1]
void DCMotor::relControl(float rel_power) {
  DCMotor::control(PER(rel_power));
}

/* Servo */
Servo::Servo(Adafruit_PWMServoDriver &_pwm, uint8_t _channel)
  : pwm(_pwm),
    channel(_channel) {}

void Servo::control(int16_t position) {
  pwm.writeMicroseconds(channel, position);
}

// rel_pos = R[0...1]
void Servo::relControl(float rel_pos) {
  Servo::control(RAW_POS_MIN + rel_pos * (RAW_POS_MAX - RAW_POS_MIN));
}

/* CRServo */
CRServo::CRServo(Adafruit_PWMServoDriver &_pwm, uint8_t _channel)
  : pwm(_pwm),
    channel(_channel) {}

void CRServo::control(int16_t speed) {
  pwm.writeMicroseconds(channel, speed);
}

// rel_speed = R[-1...1]
void CRServo::relControl(float rel_speed) {
  CRServo::control(RAW_CRSPD_M + rel_speed * (RAW_CRSPD_M - RAW_CRSPD_L));
}