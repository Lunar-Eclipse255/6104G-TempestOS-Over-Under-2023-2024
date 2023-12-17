#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"

//#include "okapi/api.hpp"

using namespace okapi;

void leftRedOneAuton(void) {
	//leftBlueOneAuton();
	driveChassis->moveDistance(50.8_cm);
	driveChassis->turnAngle(90_deg);
}