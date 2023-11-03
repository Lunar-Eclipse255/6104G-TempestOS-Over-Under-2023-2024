#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"

#include "okapi/api.hpp"

using namespace okapi;

void pSkills(void) {
    driveChassis->moveDistance(-30_cm);
    //intakeMotor.(-100, 100);
    intakeMotor.moveVoltage(-12000);
    driveChassis->turnAngle(20_deg);
    intakeMotor.moveVoltage(0);
    driveChassis->setMaxVelocity(50);
    driveChassis->moveDistance(35_cm);
    driveChassis->setMaxVelocity(1);
    driveChassis->moveDistanceAsync(1000_cm);
    catapultMotor.moveVoltage(12000);
    pros::delay(40000);
    driveChassis->stop();
    catapultMotor.moveVoltage(0);
    driveChassis->moveDistance(1000_cm);
    pros::ADIDigitalOut leftWing (WING_LEFT);
	pros::ADIDigitalOut rightWing (WING_RIGHT);
    leftWing.set_value(true);
	rightWing.set_value(true);
    driveChassis->moveDistance(1000_cm);

}