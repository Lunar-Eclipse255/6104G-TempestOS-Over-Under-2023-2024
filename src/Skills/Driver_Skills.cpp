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
    pros::delay(39000);
    chassis::turn(30, RELATIVE);
    chassis::move(90,RELATIVE);
    chassis::turn(-130, RELATIVE);
    chassis::move(50,RELATIVE);
    pneumatics::rightWingCurved.set_value(true);
    chassis::turn(90, RELATIVE);
    pneumatics::leftWingCurved.set_value(true);
    chassis::move(40,RELATIVE);
    pneumatics::leftWingCurved.set_value(false);
    pneumatics::rightWingCurved.set_value(false);
    chassis::move(-40,RELATIVE|REVERSE);
    pneumatics::rightWingCurved.set_value(true);
    pneumatics::leftWingCurved.set_value(true);
    chassis::turn(35, RELATIVE);
    chassis::move(40,RELATIVE);
    pneumatics::leftWingCurved.set_value(false);
    pneumatics::rightWingCurved.set_value(false);
    chassis::move(-40,RELATIVE|REVERSE);
    chassis::turn(-90, RELATIVE);
    chassis::move(50,RELATIVE);
    pneumatics::rightWingCurved.set_value(true);
    chassis::turn(120, RELATIVE);
    chassis::move(40,RELATIVE);
    pneumatics::leftWingCurved.set_value(false);
    pneumatics::rightWingCurved.set_value(false);
    chassis::move(-40,RELATIVE|REVERSE);
    pneumatics::rightWingCurved.set_value(true);
    pneumatics::leftWingCurved.set_value(true);
    pneumatics::rightWingDD.set_value(true);
    pneumatics::leftWingDD.set_value(true);
    pros::delay(1000);
    pneumatics::rightWingCurved.set_value(false);
    pneumatics::leftWingCurved.set_value(false);
    pneumatics::rightWingDD.set_value(false);
    pneumatics::leftWingDD.set_value(false);
}



