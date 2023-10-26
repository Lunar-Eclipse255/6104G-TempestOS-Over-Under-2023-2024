#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"

//#include "okapi/api.hpp"

using namespace okapi;

void pSkills(void) {
	drive->moveDistance(-50_cm);
    drive->moveDistance(40_cm);
}