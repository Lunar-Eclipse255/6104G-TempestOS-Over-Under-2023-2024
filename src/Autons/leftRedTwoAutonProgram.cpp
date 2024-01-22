#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"
#include "paths.hpp"

//#include "okapi/api.hpp"

using namespace okapi;

void leftRedTwoAuton(void) {
	driveChassis->setMaxVelocity(120);
    intakeMotor.moveVoltage(-12000); //might be reversed
    pros::delay(200);
    intakeMotor.moveVoltage(12000);
    pros::delay(200);
    driveChassis->turnAngle(1_deg);
    intakeMotor.moveVoltage(0);
	driveChassis->moveDistance(127_cm);
    driveChassis->turnAngle(-60_deg); //≈90 degrees
    driveChassis->setMaxVelocity(400);
    intakeMotor.moveVoltage(-12000);
    driveChassis->moveDistance(18.5_cm);
    driveChassis->moveDistance(-18_cm);
    intakeMotor.moveVoltage(0);
    driveChassis->moveDistance(18_cm);
    driveChassis->setMaxVelocity(90);
    pros::delay(200);
    intakeMotor.moveVoltage(0);
    driveChassis->moveDistance(-18_cm);
    driveChassis->turnAngle(-45_deg); //≈90 degrees
    driveChassis->setMaxVelocity(135);
    driveChassis->moveDistance(122_cm);
    driveChassis->moveDistance(-8_cm);
    driveChassis->turnAngle(57_deg);
    driveChassis->moveDistance(-110_cm);
}