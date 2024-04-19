#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"
#include "okapi/api.hpp"
#include "turn_voltage.hpp"
using namespace okapi;
using namespace arms;

void elimMatchRightAuton(void) {
    intake::init();
    pros::delay(200);
    pneumatics::rightWingDD.set_value(true);
	arms::chassis::move({25,10,60});
     intake::intakeMotor.moveVoltage(-12000);
    pneumatics::rightWingDD.set_value(false);
    arms::chassis::move(-10, REVERSE);
    chassis::turn(-20, RELATIVE);
    arms::chassis::move(16);
     arms::chassis::move(-12, REVERSE);
     chassis::turn(95, RELATIVE);
     pros::delay(1000);
     intake::intakeMotor.moveVoltage(12000);
     arms::chassis::move(50, 95, RELATIVE);
     pros::delay(500);
     intake::intakeMotor.moveVoltage(0);
     arms::chassis::move(-5, 100, REVERSE| RELATIVE);
     chassis::turn(-90, RELATIVE);
     intake::intakeMotor.moveVoltage(0);
     pros::delay(1000);
     arms::chassis::move(15, 100, RELATIVE);
     chassis::turn(-90, RELATIVE);
     pros::delay(1000);
     pneumatics::leftWingCurved.set_value(true);
    intake::intakeMotor.moveVoltage(-12000);
     arms::chassis::move(20, 100, RELATIVE);
     pneumatics::leftWingCurved.set_value(false);
    arms::chassis::move(-20, 100, RELATIVE|REVERSE);
    chassis::turn(180, RELATIVE);
    pros::delay(1000);
    intake::intakeMotor.moveVoltage(12000);
    arms::chassis::move(10, 100, RELATIVE);
    arms::chassis::move(-10, 100, RELATIVE|REVERSE);
    chassis::turn(190, RELATIVE);
    pros::delay(1000);
    intake::intakeMotor.moveVoltage(-12000);
    arms::chassis::move(20, 100, RELATIVE);
    arms::chassis::move(-20, 100, RELATIVE|REVERSE);


}