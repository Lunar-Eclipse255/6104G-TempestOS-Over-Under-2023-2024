#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"
#include "okapi/api.hpp"
using namespace okapi;

void elimMatchRightAuton(void) {
    driveChassis->setMaxVelocity(120);
	rightBlueTwoAuton();
    rightChassis.moveVoltage(1000);
    leftChassis.moveVoltage(12000);
    pros::delay(700);
    rightChassis.moveVoltage(0);
    leftChassis.moveVoltage(0);
    driveChassis->moveDistance(110_cm);

}