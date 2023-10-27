#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"

//#include "okapi/api.hpp"

using namespace okapi;

void pSkills(void) {
    intakeMotor.moveVoltage(-12000);
	drive->moveDistance(-50_cm);
    drive->moveDistance(15_cm);
    drive->turnAngle(-18_deg);
    intakeMotor.moveVoltage(0);
    drive->setMaxVelocity(50);
    drive->moveDistance(5_cm);
    drive->setMaxVelocity(1);
    drive->moveDistanceAsync(10000_cm);
    catapultMotor.moveVoltage(12000);
    pros::delay(46000);
    drive->stop();
    catapultMotor.moveVoltage(0);
}