# RiptideOS

RiptideOS is the code for the Riptide robot of the team 6104G Tempest. This  system integrates autonomous routines, operator controls, and a graphical user interfaces to maximize the robot's performance in VEX competitions.

## Table of Contents
1. [Project Overview](#project-overview)
2. [Dependencies](#dependencies)
3. [File Structure](#file-structure)
4. [Key Features](#key-features)
5. [Usage Guide](#usage-guide)
6. [Autonomous Routines](#autonomous-routines)
7. [Operator Control](#operator-control)
8. [Display System](#display-system)
9. [PID Tuning](#pid-tuning)
10. [Debugging](#debugging)
11. [License](#license)

## Project Overview

RiptideOS is built with PROS, and other libraries to enhance functionality. The code is designed to provide control over the robot's movements, offer an interface for autonomous selection and debugging, and allow for rapid iteration and improvement.

## Dependencies

This project relies on the following libraries:

1. **PROS (3.8.3)**: PROS (Purdue Robotics Operating System) is an open-source cross-platform C/C++ programming operating system for VEX robots.
2. **ARMS (3.2.0)**: Advanced Robot Motion System (ARMS) is a library providing motion control algorithms for improved precision and efficiency.
3. **gif-pros (2.1.1)**: The gif-pros is a library enabling GIF image display on the brain screen.
4. **OKAPILib (4.8.0)**: OkapiLib is a library with advanced controls and utilities for the robot, with tools for motion profiling and odometry.
5. **LVGL (5.3)**: The Light and Versatile Graphics Library (LVGL) used for creating GUIs on the Vex brain
6. **Sylib (1.0.0)**: The Sylib  library providing additional utilities and abstractions as well as LED control, it is currently included but not utilized in the code.

## File Structure

- `main.cpp`: This code sets up and manages the main functions of the robot, including initialization, disabled state handling, competition-specific setup, autonomous routines, and drive control. Using calls to namespaces and functions for different subsytems and tasks, as well as creating pros::Tasks for the functions, so the code is independant of eachother.
- `display.cpp`: This code sets up a GUI for during comp initialize using LVGL. The interface allows you to select and run autonomous routines, skills routines, and debug options, as well selecting a GIF to be displayed during the match.
- `drive.cpp`: This file sets up a drive system for the robot. It includes motor and sensor initialization, as well an arcade-style control system.
- `intake.cpp`: This code sets up an intake system for the robot. It has an initialization function to drop the intake for the match, and a control loop that manages the intake mechanism. The intake motor will turn off when it detected w/ a distance sensor that it picked up a triball, but the user can can also manually intake w/o the distance sensor if they want.
- `kicker.cpp`: This code sets up a kicker mechanism for the robot. It includes initialization for the motor and a control loop that manages the kicker. The system can toggle between manual and automatic modes.
- `pneumatics.cpp`: This code sets up various pneumatic controls for the robot. It includes initialization for pneumatic components and continuous control loops for managing these components based on user inputs. The system uses multiple controller buttons to toggle the state of each pneumatic component, providing flexible control over the robot's pneumatic mechanisms.
- `autons.hpp`: Likely contains declarations for autonomous routines.
- `motors.h`: Probably defines motor configurations and related functions.

## Key Features

1. **Autonomous Selection**: Multiple autonomous routines for different field positions and alliance colors.
2. **Operator Control**: Sophisticated teleop functions for precise robot manipulation.
3. **Custom Display System**: Intuitive interface for routine selection and system status display.
4. **GIF Support**: Ability to display GIF animations on the V5 brain screen.
5. **PID Tuning Interface**: Real-time adjustment of PID constants for optimal performance.
6. **Debug Options**: Detailed motor and sensor data display for troubleshooting.
7. **Profile Selection**: Multiple driver profiles for different control styles.

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

## License

MIT License
