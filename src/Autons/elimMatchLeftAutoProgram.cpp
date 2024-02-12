#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"
#include "okapi/api.hpp"
using namespace okapi;

void elimMatchLeftAuton(void) {

    driveChassis->setMaxVelocity(120);
	intakeMotor.moveVoltage(-12000);
    leftWing.set_value(true);
	pros::delay(700);
    intakeMotor.moveVoltage(12000);
    leftWing.set_value(false);
    rightChassis.moveVoltage(9000);
    leftChassis.moveVoltage(12000);
    pros::delay(550);
    rightChassis.moveVoltage(9000);
    leftChassis.moveVoltage(0);
    pros::delay(400);
    rightChassis.moveVoltage(0);
    driveChassis->moveDistance(31_cm);
    rightWing.set_value(true);
    driveChassis->moveDistance(-5_cm);
    driveChassis->turnAngle(90_deg);
    driveChassis->moveDistance(20_cm);
    driveChassis->turnAngle(90_deg);
    rightChassis.moveVoltage(4000);
    leftChassis.moveVoltage(12000);
    pros::delay(1000);
    rightChassis.moveVoltage(12000);
    leftChassis.moveVoltage(500);
     pros::delay(1200);
     rightChassis.moveVoltage(0);
    leftChassis.moveVoltage(0);
    driveChassis->moveDistance(80_cm);


    //driveChassis->turnAngle(-90_deg);
    //driveChassis->moveDistance(60_cm);
}