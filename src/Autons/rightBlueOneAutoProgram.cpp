#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"
#include "paths.hpp"

//#include "okapi/api.hpp"

//using namespace okapi; might be required

void rightBlueOneAuton(void) {
    generateMotionProfile(profileController);
    // Set the target and wait for the robot to settle
    profileController->setTarget("Right AWP");
    profileController->waitUntilSettled();
}