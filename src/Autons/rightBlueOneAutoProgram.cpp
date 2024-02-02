#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"
#include "okapi/api.hpp"
#define BLOCKER 'A'
using namespace okapi;

pros::ADIDigitalOut blocker (BLOCKER);
void rightBlueOneAuton(void) {


	 //do auto retraction


	
	driveChassis->setMaxVelocity(120);
	intakeMotor.moveVoltage(-12000);
	pros::delay(200);
    intakeMotor.moveVoltage(0);
	rightWing.set_value(true);
	rightChassis.moveVoltage(-5000);
	leftChassis.moveVoltage(-12000);
	pros::delay(500);
	rightWing.set_value(false);
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
	pros::delay(600);
	rightChassis.moveVoltage(6000);
	leftChassis.moveVoltage(12000);
	pros::delay(1200);
	rightChassis.moveVoltage(0);
	leftChassis.moveVoltage(0);
	driveChassis->moveDistance(75_cm);
	intakeMotor.moveVoltage(12000);
	catapultMotor.moveVoltage(12000);
	pros::delay(350);
	catapultMotor.moveVoltage(0);
	blocker.set_value(true);
	


}