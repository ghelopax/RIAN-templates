#include "hardware.h"

// ##########
// PWM DRIVER
// ##########
Adafruit_PWMServoDriver PWMDriver::pwm;
PWMDriver::PWMDriver() {
  pwm = Adafruit_PWMServoDriver();
}

void PWMDriver::init() {
  Serial.print(F("Initializing PCA9685..."));

  // PWM Init
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(50);
  // Wire Init
  Wire.setClock(400000);

  Serial.println(F("done."));
}

// ########
// HARDWARE
// ########

/* PS2 Controller */
void PS2_Controller::init() {
  Serial.print(F("Initializing PS2 controller..."));

  uint8_t error = ps2.config_gamepad(PS2_CLK, PS2_CMD, PS2_ATT, PS2_DAT);
  while (error != 0) {
    switch (error) {
      case 1:
        Serial.println("\nError code 1: No controller found, check wiring.");
        break;
      case 2:
        Serial.println("\nError code 2: Controller found but not accepting commands.");
        break;
      case 3:
        Serial.println("\nError code 3: Controller refusing to enter Pressures mode, may not support it.");
        break;
    }

    delay(1000);

    error = ps2.config_gamepad(PS2_CLK, PS2_CMD, PS2_ATT, PS2_DAT);
  }

  Serial.println(F("done."));
}

/* DC Motor */
DCMotor::DCMotor(uint8_t _channelA, uint8_t _channelB, bool _reverse)
  : channelA(_channelA),
    channelB(_channelB),
    reverse(_reverse) {}

// 12-bit pwm speed
void DCMotor::control(int16_t speed) {
  if (abs(speed) < SPD_DEAD) speed = 0;
  if (reverse) speed = -speed;

  PWMDriver::pwm.setPWM(channelA, 0, ((speed > 0) ? speed : 0));
  PWMDriver::pwm.setPWM(channelB, 0, ((speed < 0) ? (-speed) : 0));

#ifdef DEBUG_SETPWM
  Serial.print(channelA);
  Serial.print(": ");
  Serial.print(pwm.getPWM(channelA, true));
  SPC;
  Serial.print(channelB);
  Serial.print(": ");
  Serial.println(pwm.getPWM(channelB, true));
#endif
}

// rel_speed = R[-1...1]
void DCMotor::relControl(float rel_speed) {
  DCMotor::control(PER(rel_speed));
}

/* Servo */
Servo::Servo(uint8_t _channel)
  : channel(_channel) {}

void Servo::control(int16_t position) {
  PWMDriver::pwm.writeMicroseconds(channel, position);
}

// rel_pos = R[0...1]
void Servo::relControl(float rel_pos) {
  Servo::control(POS_MIN + rel_pos * (POS_MAX - POS_MIN));
}

/* CRServo */
CRServo::CRServo(uint8_t _channel)
  : channel(_channel) {}

void CRServo::control(int16_t speed) {
  PWMDriver::pwm.writeMicroseconds(channel, speed);
}

// rel_speed = R[-1...1]
void CRServo::relControl(float rel_speed) {
  CRServo::control(CRSPD_M + rel_speed * (CRSPD_M - CRSPD_L));
}