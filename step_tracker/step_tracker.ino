#include <Step_Tracker.h>

void setup() {
  // Initialise Microbit
  microbit.begin();

  // Initialise buttons
  pinMode(PIN_BUTTON_A, INPUT);
  pinMode(PIN_BUTTON_B, INPUT);

  // Initialize I2C bus
  DEV_I2C.begin();

  // Initlialize accelerometer
  Acc.begin();
  Acc.Enable();
}

void loop() {
  // Check for A press
  if (!digitalRead(PIN_BUTTON_A)) {
    countdown('A');
    steps = count_steps(A_TIME);
  }

  // Check for B press
  if (!digitalRead(PIN_BUTTON_B)) {
    countdown('B');
    steps = count_steps(B_TIME);
  }

  // Scroll step count if measured
  if (steps > -1) {
    microbit.print(steps);
  }
}
