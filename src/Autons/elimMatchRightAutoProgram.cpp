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
    arms::odom::reset({0,0},-45);
    pros::delay(200);
    pneumatics::rightWingDD.set_value(true);
	arms::chassis::move({25,-2,10});
    printf("Left: %f\n",odom::getLeftEncoder());
    printf("Right: %f\n",odom::getRightEncoder());
    if (odom::getLeftEncoder()<20||odom::getRightEncoder()<20){
        while (true){

        }
    }
    intake::intakeMotor.moveVoltage(-12000);
    pneumatics::rightWingDD.set_value(false);
    arms::chassis::move(-10, REVERSE);
    chassis::turn(-20, RELATIVE);
    arms::chassis::move(18);
     arms::chassis::move(-14, REVERSE);
     chassis::turn(110, RELATIVE);
     intake::intakeMotor.moveVoltage(12000);
     arms::chassis::move(45, RELATIVE);
     pros::delay(500);
     intake::intakeMotor.moveVoltage(0);
     arms::chassis::move(-5, 100, REVERSE| RELATIVE);
     chassis::turn(-90, RELATIVE);
     pros::delay(500);
     intake::intakeMotor.moveVoltage(0);
     arms::chassis::move(20, 100, RELATIVE);
     chassis::turn(-85, RELATIVE);
     pros::delay(500);
     pneumatics::leftWingCurved.set_value(true);
    intake::intakeMotor.moveVoltage(-12000);
     arms::chassis::move(20, 100, RELATIVE);
     pneumatics::leftWingCurved.set_value(false);
    arms::chassis::move(-20, 100, RELATIVE|REVERSE);
    chassis::turn(170, RELATIVE);
    pros::delay(500);
    intake::intakeMotor.moveVoltage(12000);
    arms::chassis::move(10, 100, RELATIVE);
    arms::chassis::move(-10, 100, RELATIVE|REVERSE);
    chassis::turn(190, RELATIVE);
    pros::delay(500);
    intake::intakeMotor.moveVoltage(-12000);
    arms::chassis::move(20, 100, RELATIVE);
    arms::chassis::move(-20, 100, RELATIVE|REVERSE);


}