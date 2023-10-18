#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"

//#include "okapi/api.hpp"

using namespace okapi;

void rightBlueAuton(void) {
    intakeMotor.moveVoltage(-12000); //might be reversed
    pros::delay(200);
    intakeMotor.moveVoltage(12000);
    pros::delay(200);
    intakeMotor.moveVoltage(0);
	drive->moveDistance(45_cm);
    drive->turnAngle(-22_deg); //≈90 degrees
    drive->moveDistance(15_cm);
    intakeMotor.moveVoltage(-12000);
    pros::delay(200);
    drive->moveDistance(-15_cm);
    drive->turnAngle(22_deg);
    drive->moveDistance(-40_cm);
    drive->turnAngle(22_deg);
    drive->moveDistance(45_cm);
}