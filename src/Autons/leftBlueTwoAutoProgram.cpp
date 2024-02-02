#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"
#include "paths.hpp"

//#include "okapi/api.hpp"

using namespace okapi;

void leftBlueTwoAuton(void) {
	driveChassis->setMaxVelocity(120);
	intakeMotor.moveVoltage(-12000);
	pros::delay(200);
    intakeMotor.moveVoltage(0);
	
	leftChassis.moveVoltage(-5000);
	rightChassis.moveVoltage(-12000);
	pros::delay(600);
	rightChassis.moveVoltage(-8000);
	leftChassis.moveVoltage(-12000);
	pros::delay(400);
	rightChassis.moveVoltage(12000);
	leftChassis.moveVoltage(12000);
	pros::delay(200);
	rightChassis.moveVoltage(-12000);
	leftChassis.moveVoltage(-12000);
	pros::delay(600);
	rightChassis.moveVoltage(12000);
	leftChassis.moveVoltage(12000);
	pros::delay(300);
	rightChassis.moveVoltage(-12000);
	leftChassis.moveVoltage(-12000);
    pros::delay(400);
     leftWing.set_value(true);
     rightChassis.moveVoltage(0);
	leftChassis.moveVoltage(0);
     driveChassis->turnAngle(-40_deg);//was 30
	leftChassis.moveVoltage(5500);
	rightChassis.moveVoltage(12000);
	pros::delay(1000);
	rightChassis.moveVoltage(0);
	leftChassis.moveVoltage(0);
    driveChassis->turnAngle(-90_deg);
    driveChassis->moveDistance(20_cm);
    leftWing.set_value(false);
    intakeMotor.moveVoltage(-12000);
	catapultMotor.moveVoltage(12000);
	pros::delay(350);
	catapultMotor.moveVoltage(0);
    
	
    
}