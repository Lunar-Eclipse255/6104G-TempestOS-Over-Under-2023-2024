#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"
#include "okapi/api.hpp"
using namespace okapi;

void rightBlueOneAuton(void) {
	driveChassis->setMaxVelocity(120);
	intakeMotor.moveVoltage(-12000);
	pros::delay(200);
    intakeMotor.moveVoltage(12000);
	driveChassis->moveDistance(20_cm);
	intakeMotor.moveVoltage(500);
	driveChassis->moveDistance(-106_cm);
	driveChassis->turnAngle(-43_deg);
	rightWing.set_value(true);
	driveChassis->moveDistance(-45_cm);
	driveChassis->turnAngle(-23_deg);
}