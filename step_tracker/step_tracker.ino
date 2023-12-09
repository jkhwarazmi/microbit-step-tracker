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
  int32_t accelerometer[3];

  // Count a step if z-axis acceleration is over the threshold
  Acc.GetAxes(accelerometer);
  if (abs(accelerometer[2]) > MIN_ACCELERATION) {
    steps++;
  }

  // Print z-axis and steps to the serial plotter
  Serial.print("Z:");
  Serial.print(accelerometer[2]);
  Serial.print(",Steps:");
  Serial.println(steps);

  delay(20);
}
