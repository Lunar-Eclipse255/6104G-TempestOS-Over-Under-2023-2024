#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"
#include "okapi/api.hpp"
#define WING_LEFT 'B'
#define WING_RIGHT 'C'
using namespace okapi;
pros::ADIDigitalOut leftWing (WING_LEFT);
pros::ADIDigitalOut rightWing (WING_RIGHT);
void pSkills(void) {
    intakeMotor.moveVoltage(-12000);
	pros::delay(200);
    intakeMotor.moveVoltage(0);
    driveChassis->moveDistance(-4_cm);
    driveChassis->turnAngle(-18_deg);
    driveChassis->moveDistance(1_cm);
    catapultMotor.moveVoltage(9000);
    pros::delay(41000);
    
    driveChassis->setMaxVelocity(120);
    driveChassis->moveDistance(-4_cm);
    catapultMotor.moveVoltage(0);
    driveChassis->turnAngle(-31.5_deg);
    driveChassis->moveDistance(-210_cm);
    driveChassis->turnAngle(90_deg);
    driveChassis->moveDistance(-60_cm);
    driveChassis->turnAngle(85_deg);
    driveChassis->moveDistance(-44_cm);
    driveChassis->turnAngle(89_deg);
    driveChassis->moveDistance(79_cm);
    driveChassis->turnAngle(89_deg);
    leftWing.set_value(true);
    rightWing.set_value(true);
    driveChassis->setMaxVelocity(600);
    driveChassis->moveDistance(-80_cm);

    
}