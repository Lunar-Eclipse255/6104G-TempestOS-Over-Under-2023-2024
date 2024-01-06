#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"
#include "paths.hpp"

//#include "okapi/api.hpp"

using namespace okapi;

void leftBlueOneAuton(void) {
	generateMotionProfile(profileController);
    // Set the target and wait for the robot to settle
    profileController->setTarget("Left AWP");
    profileController->waitUntilSettled();
}