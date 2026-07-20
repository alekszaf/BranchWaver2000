# BranchWaver2000

BranchWaver2000 is an Arduino-controlled mechatronics project designed to simulate organic, back-and-forth branch movement for motion-tracking experiments. This repository contains the necessary 3D printable part designs and the Arduino control sketches. 

## Project Components

### Hardware
The mechanical structure can be created by 3D printing the included STL files.
*   **`STL/motorMount.stl`**: Mount for the stepper motor.
*   **`STL/Coupler.stl`**: A coupler to attach an object to the motor shaft.
*   **`STL/HolderCover.stl`**: A cover for part of the assembly.

### Software
The control logic is provided as Arduino sketches.
*   **`bounce_simple/bounce_simple.ino`**: The primary control sketch that uses the `AccelStepper` library for smooth, continuous motion. It is controlled via the serial monitor.
*   **`motorTest/motorTest.ino`**: A basic sketch for testing and jogging the motor to specific angles.

## Installation and Usage

1.  **Hardware Setup**:
    *   3D print the required parts located in the `STL/` directory.
    *   Assemble the parts with a stepper motor, an Arduino, and a suitable motor driver.

2.  **Software Setup**:
    *   Install the [AccelStepper library](http://www.airspayce.com/mikem/arduino/AccelStepper/) in your Arduino IDE.
    *   Connect your Arduino board to the computer.
    *   Upload the `bounce_simple/bounce_simple.ino` sketch to your board.

3.  **Operation**:
    *   Open the Arduino IDE Serial Monitor and set the baud rate to **115200**.
    *   Use the following commands to control the device:
        *   `s` - Starts the waving motion.
        *   `n` - Stops the motion and disables the motor.
        *   `a<value>` - Sets the motor acceleration in steps/second². (e.g., `a2000`)
        *   `v<value>` - Sets the maximum motor speed in steps/second. (e.g., `v3000`)
        *   `d<value>` - Sets the swing distance in steps. The motion will swing from `-value` to `+value`. (e.g., `d533`)

## License

This project is licensed under the GNU General Public License v3.0. See the `LICENSE` file for full details.
