#pragma once

// #####
// MACRO
// #####

#define SPC Serial.print(" ")
#define PER(percentage)  (int16_t)(SPD_MAX * (percentage))
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

// Motor speed
#define SPD_MAX          4095
#define SPD_DEAD         70

#define SPD_INTAKE       1.00

// Servo position 
#define POS_MIN          440
#define POS_MAX          2270

// CRServo speed
#define CRSPD_L          400
#define CRSPD_M          1400

/* PWM channels */
// Drivetrain
#define LF_A             6      // Mecanum Drive
#define LF_B             7
#define LB_A             4
#define LB_B             5
#define RF_A             2
#define RF_B             3
#define RB_A             0
#define RB_B             1

// Subsystems
#define IT_A             12     // Intake
#define IT_B             13

// Servo
#define OT_S             14

/* PS2 pins */
#define PS2_DAT          13
#define PS2_CMD          11
#define PS2_ATT          10
#define PS2_CLK          12




