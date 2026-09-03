#pragma once

// #############
// CONFIGURATION
// #############

/* CONSTANTS */
// Motor speed
#define SPD_MAX          4095
#define SPD_DEAD         70
#define PER(percentage)  (int16_t)(SPD_MAX * (percentage))

#define SPD_DRIVE_LF     1.00
#define SPD_DRIVE_LB     1.00
#define SPD_DRIVE_RF     1.00
#define SPD_DRIVE_RB     1.00
#define SPD_SLIDE        1.00
#define SPD_INTAKE       1.00
#define SPD_CONVEY       0.80

// Servo position 
#define POS_MIN          440
#define POS_MAX          2270

// CRServo speed
#define CRSPD_L          400
#define CRSPD_M          1400

/* PWM channels */
// DC Motor
// Drivetrain
#define LF_A             6      // Mecanum Drive
#define LF_B             7
#define LB_A             4
#define LB_B             5
#define RF_A             2
#define RF_B             3
#define RB_A             0
#define RB_B             1

// Subsystem
#define LS_A             8      // Linear Slide
#define LS_B             9

#define IT_A             12     // Intake
#define IT_B             13

#define CB_A             10     // Conveyor Belt
#define CB_B             11

// Servo
#define S_OT             14

/* PS2 pins */
#define PS2_DAT          13
#define PS2_CMD          11
#define PS2_ATT          10
#define PS2_CLK          12




