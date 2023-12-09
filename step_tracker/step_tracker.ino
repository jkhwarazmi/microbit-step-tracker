#include "LSM303AGR_ACC_Sensor.h"  // Include ACC Sensor library

#define DEV_I2C Wire1  // Defines which I2C bus is used - Wire1 for the Microbit V2
#define MIN_ACCELERATION 1200  // Minimum acceleration for a step

LSM303AGR_ACC_Sensor Acc(&DEV_I2C);

int steps = 0;  // Initial step count

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

  // Count a step if acceleration is over the threshold
  if (magnitude > MIN_ACCELERATION) {
    steps++;
  }

  // Print magnitude and steps to the serial plotter
  Serial.print("Magnitude:");
  Serial.print(magnitude);
  Serial.print(",Steps:");
  Serial.println(steps);

  delay(20);
}
