#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"

//#include "okapi/api.hpp"

using namespace okapi;

void rightBlueAuton(void) {
    drive->setMaxVelocity(100);
    intakeMotor.moveVoltage(-12000); //might be reversed
    pros::delay(200);
    intakeMotor.moveVoltage(12000);
    pros::delay(200);
    drive->turnAngle(-1_deg);
    intakeMotor.moveVoltage(0);
	drive->moveDistance(132.5_cm);
    drive->turnAngle(68_deg); //≈90 degrees
    intakeMotor.moveVoltage(-12000);
    drive->moveDistance(25.5_cm);
    pros::delay(200);
    intakeMotor.moveVoltage(0);
    drive->moveDistance(-15_cm);
    drive->turnAngle(45_deg); //≈90 degrees
    drive->moveDistance(60_cm);
    /*
    drive->moveDistance(-30_cm);
    drive->turnAngle(22_deg);
    drive->moveDistance(40_cm);
    drive->turnAngle(22_deg);
    drive->moveDistance(45_cm);
    */
}