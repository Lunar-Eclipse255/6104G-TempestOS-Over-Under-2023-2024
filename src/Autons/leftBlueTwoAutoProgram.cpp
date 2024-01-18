#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"
#include "paths.hpp"

//#include "okapi/api.hpp"

using namespace okapi;

void leftBlueTwoAuton(void) {
	driveChassis->setMaxVelocity(200);
	driveChassis->moveDistance(-200_cm);
	driveChassis->moveDistance(200_cm);
	//driveChassis->turnAngle(90_deg);
}