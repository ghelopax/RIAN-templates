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

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <PS2X_lib.h>

// #####
// MACRO
// #####

#define PER(percentage)  (int16_t)(RAW_POW_MAX * (percentage))
#define fMAP(x, l, r, L, R) ((float)(x - l)/(r - l) * (R - L) + L)


// #############     
// CONFIGURATION
// #############

/* CONSTANTS */
// Calibration
#define CAL_DRIVE_LF     1.00
#define CAL_DRIVE_LB     1.00
#define CAL_DRIVE_RF     1.00
#define CAL_DRIVE_RB     1.00

// Motor power
#define RAW_POW_MAX      4095
#define RAW_POW_DEAD     70

#define POW_INTAKE       1.00

// Servo position 
#define RAW_POS_MIN      440
#define RAW_POS_MAX      2270

// CRServo speed
#define RAW_CRSPD_L      400
#define RAW_CRSPD_M      1400

/* PWM channels */
// Drivetrain: Mecanum Drive
#define LF_A             6
#define LF_B             7
#define LB_A             4
#define LB_B             5
#define RF_A             2
#define RF_B             3
#define RB_A             0
#define RB_B             1

// Intake
#define IT_A             12
#define IT_B             13

/* PS2 pins */
#define PS2_DAT          13
#define PS2_CMD          11
#define PS2_ATT          10
#define PS2_CLK          12