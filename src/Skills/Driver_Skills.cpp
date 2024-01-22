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
    //driveChassis->turnAngle(90_deg);
	
}



