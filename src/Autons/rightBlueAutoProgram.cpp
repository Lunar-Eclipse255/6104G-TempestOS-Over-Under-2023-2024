#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"

//#include "okapi/api.hpp"

//using namespace okapi; might be required

void rightBlueAuton(void) {
    drive->setMaxVelocity(150);
    intakeMotor.moveVoltage(-12000); //might be reversed
    pros::delay(200);
    intakeMotor.moveVoltage(12000);
    pros::delay(200);
    drive->turnAngle(-1_deg);
    intakeMotor.moveVoltage(0);
	drive->moveDistance(130_cm);
    drive->turnAngle(68_deg); //≈90 degrees
    intakeMotor.moveVoltage(-12000);
    drive->moveDistance(18.5_cm);
    pros::delay(200);
    intakeMotor.moveVoltage(0);
    drive->moveDistance(-21_cm);
    drive->turnAngle(45_deg); //≈90 degrees
    drive->moveDistance(130_cm);

}