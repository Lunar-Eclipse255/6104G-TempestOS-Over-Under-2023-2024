#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"

//#include "okapi/api.hpp"

//using namespace okapi; might be required

void rightBlueAuton(void) {
    drive->setMaxVelocity(120);
    intakeMotor.moveVoltage(-12000); //might be reversed
    pros::delay(200);
    intakeMotor.moveVoltage(12000);
    pros::delay(200);
    drive->turnAngle(-1_deg);
    intakeMotor.moveVoltage(0);
	drive->moveDistance(127_cm);
    drive->turnAngle(63_deg); //≈90 degrees
    drive->setMaxVelocity(400);
    intakeMotor.moveVoltage(-12000);
    drive->moveDistance(18.5_cm);
    drive->setMaxVelocity(90);
    pros::delay(200);
    intakeMotor.moveVoltage(0);
    drive->moveDistance(-19.5_cm);
    drive->turnAngle(45_deg); //≈90 degrees
    drive->setMaxVelocity(135);
    drive->moveDistance(145_cm);
    drive->moveDistance(-5_cm);
    drive->turnAngle(-65_deg);

}