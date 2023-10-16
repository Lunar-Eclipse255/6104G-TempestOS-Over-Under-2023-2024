#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"

//#include "okapi/api.hpp"

using namespace okapi;

void rightBlueAuton(void) {
    intakeMotor.moveVoltage(12000); //might be reversed
    pros::delay(800);
    intakeMotor.moveVoltage(0);
	drive->moveDistance(40_cm);
}