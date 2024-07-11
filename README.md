# RiptideOS

RiptideOS is the comprehensive operating system for the Riptide robotics team's VEX V5 robot. This advanced system integrates autonomous routines, operator controls, and a sophisticated user interface to maximize the robot's performance in VEX competitions.

## Table of Contents
1. [Project Overview](#project-overview)
2. [Dependencies](#dependencies)
3. [File Structure](#file-structure)
4. [Key Features](#key-features)
5. [Setup and Installation](#setup-and-installation)
6. [Usage Guide](#usage-guide)
7. [Autonomous Routines](#autonomous-routines)
8. [Operator Control](#operator-control)
9. [Display System](#display-system)
10. [PID Tuning](#pid-tuning)
11. [Debugging](#debugging)
12. [Contributing](#contributing)
13. [License](#license)
14. [Contact](#contact)

## Project Overview

RiptideOS is built on the PROS development environment, leveraging several additional libraries to enhance functionality and ease of development. The system is designed to provide precise control over the robot's movements, offer an intuitive interface for routine selection and debugging, and allow for rapid iteration and improvement of robot performance.

## Dependencies

This project relies on the following libraries:

1. **PROS (3.8.3)**: The core development environment for VEX V5 robots.
2. **ARMS (3.2.0)**: Advanced Robot Motion System, providing enhanced motion control algorithms.
3. **gif-pros (2.1.1)**: Enables GIF display on the V5 brain's screen.
4. **okapilib (4.8.0)**: Offers a comprehensive suite of utilities for advanced robot control.
5. **sylib (1.0.0)**: SYLib robotics library, providing additional utilities and abstractions.

## File Structure

- `main.cpp`: Contains the program entry point, autonomous routines, and operator control code.
- `display.cpp`: Manages the custom LCD display system and user interface.
- `autons.hpp`: Likely contains declarations for autonomous routines.
- `motors.h`: Probably defines motor configurations and related functions.
- Additional files (not visible in provided snippets) may handle specific subsystems, sensors, and utilities.

## Key Features

1. **Autonomous Selection**: Multiple autonomous routines for different field positions and alliance colors.
2. **Operator Control**: Sophisticated teleop functions for precise robot manipulation.
3. **Custom Display System**: Intuitive interface for routine selection and system status display.
4. **GIF Support**: Ability to display GIF animations on the V5 brain screen.
5. **PID Tuning Interface**: Real-time adjustment of PID constants for optimal performance.
6. **Debug Options**: Detailed motor and sensor data display for troubleshooting.
7. **Profile Selection**: Multiple driver profiles for different control styles.

## Setup and Installation

1. Install PROS on your development machine (version 3.8.3 or later recommended).
2. Clone this repository:git clone https://github.com/your-team/RiptideOS.git

3. Open the project in a PROS-compatible IDE (like Visual Studio Code with PROS extension).
4. Install required libraries through the PROS CLI or IDE interface.
5. Compile the project to ensure all dependencies are correctly linked.

## Usage Guide

1. **Compile the Project**: Use the PROS CLI or IDE to compile the project.
2. **Upload to V5 Brain**: Connect your V5 brain and upload the compiled program.
3. **Select Autonomous Routine**: Use the touch screen interface to choose the appropriate autonomous routine before the match.
4. **Monitor Status**: During operation, the screen will display relevant status information.

## Autonomous Routines

The system includes several autonomous routines:

- `rightRedOneAuton`, `rightRedTwoAuton`, `elimMatchRightAuton`: Right-side routines for red alliance
- `leftRedOneAuton`, `leftRedTwoAuton`, `elimMatchLeftAuton`: Left-side routines for red alliance
- `rightBlueOneAuton`, `rightBlueTwoAuton`: Right-side routines for blue alliance
- `leftBlueOneAuton`, `leftBlueTwoAuton`: Left-side routines for blue alliance
- `pSkills`, `dSkills`: Programming and driving skills routines

## Operator Control

The operator control system includes:

- Intake control
- Kicker mechanism control
- Pneumatic systems management (dropdowns, curved mechanisms, PTO)
- Chassis control with potential for different drive modes

## Display System

The custom display system features:

- Multiple screen layouts for different functions (autonomous selection, skills, debug, etc.)
- Dropdown menus for easy navigation and selection
- GIF display capabilities for visual feedback
- PID constant adjustment interface

## PID Tuning

The PID tuning interface allows for real-time adjustment of kP, kI, and kD constants, enabling rapid optimization of control loops for various robot mechanisms.

## Debugging

Debug options include:

- Motor information display
- PID loop performance visualization
- Sensor data readouts

## Contributing

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

Please coordinate with the programming lead before making significant changes.

## License