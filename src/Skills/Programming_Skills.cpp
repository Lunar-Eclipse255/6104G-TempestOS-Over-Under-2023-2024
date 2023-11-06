#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"

#include "okapi/api.hpp"

using namespace okapi;

void pSkills(void) {
    driveChassis->moveDistance(-30_cm);
    //intakeMotor.(-100, 100);
    intakeMotor.moveVoltage(-12000);
    driveChassis->turnAngle(-20_deg);
    intakeMotor.moveVoltage(0);
    driveChassis->setMaxVelocity(50);
    driveChassis->moveDistance(32_cm);
    driveChassis->setMaxVelocity(1);
    driveChassis->moveDistanceAsync(1000_cm);
    catapultMotor.moveVoltage(12000);
    pros::delay(40000);

    
}