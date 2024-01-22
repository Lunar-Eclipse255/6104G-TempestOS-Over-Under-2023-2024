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
    driveChassis->setMaxVelocity(120);
    intakeMotor.moveVoltage(-12000);
	pros::delay(200);
    intakeMotor.moveVoltage(0);
    pros::delay(200);
    driveChassis->moveDistance(-38_cm);
    driveChassis->turnAngle(-80_deg);
    driveChassis->moveDistance(30_cm);
    /*
    driveChassis->turnAngle(100_deg);
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
    driveChassis->moveDistance(80_cm);
    */
    
}