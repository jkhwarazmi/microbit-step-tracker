#include "LSM303AGR_ACC_Sensor.h"  // Include ACC Sensor library

#define DEV_I2C Wire1  // Defines which I2C bus is used - Wire1 for the Microbit V2
#define MIN_ACCELERATION 1200  // Minimum acceleration for a step
#define MIN_STEP_TIME 300  // Minimum time between steps

LSM303AGR_ACC_Sensor Acc(&DEV_I2C);

int steps = 0;  // Initial step count
int last_step_time = 0;  // Time since last step

void setup() {
  // Initialise serial for plotting
  Serial.begin(115200);

  // Initialize I2C bus
  DEV_I2C.begin();

  // Initlialize accelerometer
  Acc.begin();
  Acc.Enable();
}

void loop() {
  int32_t accelerometer[3];  // Initialise accelerometer data array

  // Get accelerometer data and calculate magnitude of acceleration
  Acc.GetAxes(accelerometer);
  double magnitude = sqrt(pow(accelerometer[0], 2) + pow(accelerometer[1], 2) + pow(accelerometer[2], 2));

  // If acceleration enough for a step and more than the minimum time between steps has passed, increase step count and reset last step time
  if (magnitude > MIN_ACCELERATION && (millis() - last_step_time) > MIN_STEP_TIME) {
    steps++;
    last_step_time = millis();
  }

  // Print magnitude and steps to the serial plotter
  Serial.print("Magnitude:");
  Serial.print(magnitude);
  Serial.print(",Steps:");
  Serial.println(steps);

  delay(20);
}
