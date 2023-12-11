#ifndef STEP_TRACKER_H
#define STEP_TRACKER_H

#include "Adafruit_Microbit.h"  // Include Adafruit Microbit library
#include "LSM303AGR_ACC_Sensor.h"  // Include ACC Sensor library

#define DEV_I2C Wire1  // Defines which I2C bus is used - Wire1 for the Microbit V2
#define MIN_ACCELERATION 1450  // Minimum acceleration for a step
#define MIN_STEP_TIME 300  // Minimum time between steps
#define A_TIME 300000  // Time to record steps for if A pressed
#define B_TIME 30000  // Time to record steps for if B pressed

void countdown(char mode);  // Countdown function
int count_steps(int time);  // Step counting function

// Forward declarations of global variables
extern LSM303AGR_ACC_Sensor Acc;
extern Adafruit_Microbit_Matrix microbit;
extern int steps;

#endif /* STEP_TRACKER_H */
