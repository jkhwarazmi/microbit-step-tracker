#include "Step_Tracker.h"

// Components
LSM303AGR_ACC_Sensor Acc(&DEV_I2C);
Adafruit_Microbit_Matrix microbit;

int steps = -1;  // Initial step count

// Displays a 5 second countdown and then the mode name
void countdown(char mode) {
  // Count down for 5 seconds
  for (int i = 5; i > 0; i--) {
    microbit.print(i);
    delay(1000);
  }

  // Display mode of operation
  if (mode == 'A') {
    microbit.print("A");
  } else {
    microbit.print("B");
  }
}

// Counts steps for a given time in ms and returns the step count
int count_steps(int time) {
  int start = millis();  // Start time of step counting
  int current_steps = 0;  // Steps counted
  int last_step_time = 0;  // Time since last step
  int32_t accelerometer[3];  // Initialise accelerometer data array

  // While within time for counting
  while ((millis() - start) < time) {

    // Get accelerometer data and calculate magnitude of acceleration
    Acc.GetAxes(accelerometer);
    double magnitude = sqrt(pow(accelerometer[0], 2) + pow(accelerometer[1], 2) + pow(accelerometer[2], 2));

    // If acceleration enough for a step and more than the minimum time between steps has passed, increase step count and reset last step time
    if (magnitude > MIN_ACCELERATION && (millis() - last_step_time) > MIN_STEP_TIME) {
      current_steps++;
      last_step_time = millis();
    }
  }

  // Return our new step count
  return current_steps;
}
