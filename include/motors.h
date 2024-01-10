#include "main.h"
#define WING_LEFT 'B'
#define WING_RIGHT 'C'
#include "lemlib/api.hpp"
//declares the motors, chassis, and ADIButton

extern Motor intakeMotor;
extern Motor catapultMotor;
extern ADIButton catapultLimit;
extern lemlib::Chassis chassis;
extern pros::ADIDigitalOut leftWing ();
extern pros::ADIDigitalOut rightWing ();


