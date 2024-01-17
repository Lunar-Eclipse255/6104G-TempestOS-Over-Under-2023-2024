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
    driveChassis->turnAngle(-18_deg);
    catapultMotor.moveVoltage(9000);
    pros::delay(700);
    //pros::delay(47000);
    catapultMotor.moveVoltage(0);
    driveChassis->moveDistance(-3.5_cm);
    driveChassis->turnAngle(-28_deg);
    driveChassis->moveDistance(-200_cm);
    driveChassis->turnAngle(92_deg);
    driveChassis->moveDistance(-57_cm);
    driveChassis->turnAngle(-90_deg);
    driveChassis->moveDistance(40_cm);
    driveChassis->turnAngle(-90_deg);
    driveChassis->moveDistance(90_cm);
    driveChassis->turnAngle(90_deg);
    leftWing.set_value(true);
    rightWing.set_value(true);
    while (true){
        driveChassis->moveDistance(-50_cm);
        driveChassis->moveDistance(50_cm);
    }
}