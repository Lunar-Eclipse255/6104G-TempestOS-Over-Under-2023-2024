#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"


//#include "okapi/api.hpp"

using namespace okapi;

void dSkills(void) {
	//pros::screen::set_pen(COLOR_BLUE);
    //pros::screen::print(pros::E_TEXT_MEDIUM, 3, "Drive Flag");
    driveChassis->setMaxVelocity(120);
    intakeMotor.moveVoltage(-12000);
	pros::delay(200);
    intakeMotor.moveVoltage(0);
    pros::delay(200);
    driveChassis->moveDistance(-38_cm);
    driveChassis->turnAngle(-75_deg);
    driveChassis->setMaxVelocity(50);
    driveChassis->moveDistance(34_cm);
    //driveChassis->turnAngle(90_deg);
	
}



