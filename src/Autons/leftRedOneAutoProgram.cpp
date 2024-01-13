#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"
#include "paths.hpp"

//#include "okapi/api.hpp"

using namespace okapi;

void leftRedOneAuton(void) {
	intakeMotor.moveVoltage(12000);
	driveChassis->moveDistance(2.2_ft);
	driveChassis->moveDistance(-2_ft);
	intakeMotor.moveVoltage(0);
	driveChassis->moveDistance(-2_ft);

}