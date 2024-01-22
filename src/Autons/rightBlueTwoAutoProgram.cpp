#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"
#include "paths.hpp"
//#include "okapi/api.hpp"

//using namespace okapi; might be required

void rightBlueTwoAuton(void) {
    driveChassis->setMaxVelocity(120);
	intakeMotor.moveVoltage(-12000);
	pros::delay(200);
    intakeMotor.moveVoltage(12000);
	driveChassis->setMaxVelocity(70);
	driveChassis->moveDistance(20_cm);
	intakeMotor.moveVoltage(500);
	driveChassis->moveDistance(-106_cm);
	driveChassis->setMaxVelocity(50);
	driveChassis->turnAngle(-43_deg);
	rightWing.set_value(true);

	driveChassis->moveDistance(-45_cm);
	driveChassis->turnAngle(-23_deg);
	rightWing.set_value(false);
	driveChassis->setMaxVelocity(120);
	pros::delay(200);
	driveChassis->turnAngle(-26_deg);
	driveChassis->moveDistance(-20_cm);
	driveChassis->turnAngle(-13_deg);
	driveChassis->moveDistance(10_cm);
	driveChassis->setMaxVelocity(600);
	driveChassis->moveDistance(-30_cm);
	driveChassis->moveDistance(25_cm);
	driveChassis->setMaxVelocity(600);
	driveChassis->moveDistance(-30_cm);
	driveChassis->moveDistance(15_cm);
	driveChassis->turnAngle(-112_deg);
	driveChassis->moveDistance(-110_cm);
	intakeMotor.moveVoltage(-12000);
	intakeMotor.moveVoltage(0);
	driveChassis->turnAngle(45_deg);
	driveChassis->moveDistance(-55_cm);
	rightWing.set_value(true);
	leftWing.set_value(true);

	//driveChassis->moveDistance(15_cm);
	//driveChassis->setMaxVelocity(600);
	//driveChassis->moveDistance(-60_cm);
	//driveChassis->moveDistance(60_cm);

	//driveChassis->moveDistance(-60_cm);
}
