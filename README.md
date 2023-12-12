# Micro:bit Step Tracker

A step counter for the BBC Micro:bit V2, written in C using the Arduino IDE. The aim was to use the Micro:bit's accelerometer to count steps over a 5 minute period and give the user a way of seeing the result.

## Features

- Two counting modes: 5 minutes (button A) or 30 seconds (button B)
- 5 second countdown before counting starts, giving you time to put the Micro:bit in your pocket
- Step count scrolls across the LED matrix once counting has finished
- Instructions are shown on the display whenever the board is reset
- Uses all three axes of the accelerometer, so the orientation of the Micro:bit doesn't matter

## How It Works

### Reading the Accelerometer

The Micro:bit V2 has an LSM303AGR accelerometer on its internal I2C bus (`Wire1`), which gives a reading for the x, y and z axes in milli-g. Before writing any step detection I printed the raw values to the Arduino IDE's Serial Plotter to get a feel for the data. With the Micro:bit lying flat and still, z sat at around -1000 due to gravity while x and y stayed close to 0.

My first attempt counted a step whenever the z-axis reading went past a threshold. That didn't last long, as shaking the board around showed how much each axis depends on the orientation of the Micro:bit, and there's no way of controlling that when it's in your pocket.

### Step Detection

Instead, the program calculates the magnitude of acceleration across all three axes:

```
magnitude = sqrt(x² + y² + z²)
```

This gives a single value regardless of which way up the Micro:bit is. At rest it's roughly 1000 (gravity), and a step is counted when it goes over `MIN_ACCELERATION`.

A threshold on its own wasn't enough though. The magnitude stays above it for several readings at each peak, so one step was being counted multiple times. To get around this there's also a minimum time between steps (`MIN_STEP_TIME`). Walking briskly I took about 50 steps in 30 seconds, roughly 600ms per step, so I halved that to 300ms to allow for quicker steps. A step is only counted if the magnitude is over the threshold **and** at least 300ms have passed since the last one, which is checked using `millis()`.

### Choosing the Threshold

The threshold had to be above 1000 but it wasn't obvious by how much, so it was found through testing with the Micro:bit in my pocket. I started with 30 second walks and counted my steps manually. 1200 overcounted by around 15% in both tests, while 1300 was much closer at 2.7%.

After that I moved on to 5 minute walks, using my Fitbit as the reference:

| Threshold | Tests | Average Difference from Fitbit |
|-----------|-------|--------------------------------|
| 1200      | 1     | 7.89%                          |
| 1300      | 2     | 6.99%                          |
| 1400      | 2     | 4.52%                          |
| 1450      | 3     | 3.13%                          |
| 1500      | 2     | 5.67%                          |

Everything up to 1400 overcounted and 1500 undercounted. 1450 landed either side of the Fitbit count and was the closest on average, so that's the value used. These values were tuned for my own walking with the Micro:bit in my pocket, so if you're wearing it differently it may be worth adjusting `MIN_ACCELERATION` in `Step_Tracker.h`.

## Usage

1. Power on or reset the Micro:bit and it will scroll `STEP TRACKER   A = 5M   B = 30S`
2. Press **A** to count steps for 5 minutes or **B** for 30 seconds
3. A countdown from 5 is shown, then the letter of the selected mode stays on screen while counting
4. Once the time is up, the number of steps scrolls across the display on repeat

To start a new count, press A or B again. The scrolling text blocks while it's being displayed, so the button press is only picked up once the current scroll has finished. Holding the button down until then works fine.

## Project Structure

```
.
├── libraries/
│   └── Step_Tracker/
│       ├── Step_Tracker.h      # Constants, function prototypes and global variable declarations
│       └── Step_Tracker.cpp    # Countdown and step counting functions
└── step_tracker/
    └── step_tracker.ino        # Setup and main loop
```

The step tracking logic is kept in its own library so the sketch itself only has to deal with setup, input and output. The source file uses a `.cpp` extension since that's what the Arduino IDE expects, but the code is written in a procedural C style (the only C++ is the use of the accelerometer and LED matrix library objects).

## Installation

### Requirements

- BBC Micro:bit V2
- [Arduino IDE](https://www.arduino.cc/en/software)
- Nordic Semiconductor nRF5 board package
- [Adafruit Microbit Library](https://github.com/adafruit/Adafruit_Microbit)
- [STM32duino LSM303AGR](https://github.com/stm32duino/LSM303AGR) library (provides `LSM303AGR_ACC_Sensor`)

### Steps

1. Clone the repository:
```bash
git clone https://github.com/jkhwarazmi/microbit-step-tracker.git
```

2. In the Arduino IDE, go to **Preferences** and add the following to **Additional boards manager URLs**:
```
https://sandeepmistry.github.io/arduino-nRF5/package_nRF5_boards_index.json
```

3. Install **Nordic Semiconductor nRF5 Boards** from the Boards Manager, and the Adafruit Microbit and STM32duino LSM303AGR libraries from the Library Manager.

4. Copy the `libraries/Step_Tracker` folder into your Arduino libraries folder (usually `Documents/Arduino/libraries`).

5. Open `step_tracker/step_tracker.ino`, select **BBC micro:bit V2** as the board, plug in the Micro:bit and upload.

## Limitations

- The step count isn't saved anywhere, so it's lost when the board is reset or a new count is started
- Counting can't be cancelled early, other than by resetting the board
- The threshold was tuned for one person with the Micro:bit in a pocket, so accuracy will vary depending on the user and where it's worn
