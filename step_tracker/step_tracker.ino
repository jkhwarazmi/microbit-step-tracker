#include "LSM303AGR_ACC_Sensor.h"  // Include ACC Sensor library

#define DEV_I2C Wire1  // Defines which I2C bus is used - Wire1 for the Microbit V2

LSM303AGR_ACC_Sensor Acc(&DEV_I2C);

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

  // Print each axis to the serial plotter
  Acc.GetAxes(accelerometer);
  Serial.print("X:");
  Serial.print(accelerometer[0]);
  Serial.print(",Y:");
  Serial.print(accelerometer[1]);
  Serial.print(",Z:");
  Serial.println(accelerometer[2]);

  delay(20);
}
