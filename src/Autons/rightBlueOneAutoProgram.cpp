#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"
#include "okapi/api.hpp"
#include "turn_voltage.hpp"
#include "ARMS/config.h"
using namespace okapi;

void rightBlueOneAuton(void) {

    arms::odom::reset({0,0},0);
	arms::chassis::move({30,10,45});
    arms::chassis::move(-10,arms::REVERSE);
    
}
