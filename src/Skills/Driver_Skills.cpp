#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"
#include "okapi/api.hpp"
#include "turn_voltage.hpp"
#include "ARMS/config.h"
using namespace arms;

void dSkills(void) {
    intake::init();
	kicker::kickerMotor.moveVoltage(12000);
    chassis::turn(30, RELATIVE);
    chassis::move(90,RELATIVE);
    chassis::turn(-130, RELATIVE);
    chassis::move(50,RELATIVE);
    chassis::turn(90, RELATIVE);
    pneumatics::leftWingCurved.set_value(true);
    pneumatics::rightWingCurved.set_value(true);
    chassis::move(40,RELATIVE);
    chassis::move(-40,RELATIVE|REVERSE);
    chassis::turn(35, RELATIVE);
    chassis::move(40,RELATIVE);
    chassis::move(-40,RELATIVE|REVERSE);
    chassis::turn(70, RELATIVE);
    chassis::move(40,RELATIVE);
    chassis::move(-40,RELATIVE|REVERSE);
}



