#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"
#include "okapi/api.hpp"
#include "turn_voltage.hpp"
#include "ARMS/config.h"
using namespace arms;

void rightBlueOneAuton(void) {
    intake::init();
    pros::delay(200);
    pneumatics::rightWingDD.set_value(true);
	arms::chassis::move({23,18,55});
    if (odom::getLeftEncoder()<20||odom::getRightEncoder()<20){
        while (true){

        }
    }
     intake::intakeMotor.moveVoltage(-12000);
    pneumatics::rightWingDD.set_value(false);
    pros::delay(1000);
    arms::chassis::move(-10, REVERSE);
    chassis::turn(-25, RELATIVE);
    arms::chassis::move(14);
     arms::chassis::move(-12, REVERSE);
     arms::chassis::move(16,100);
     arms::chassis::move(-12, REVERSE);
    pros::delay(500);
    chassis::turn(160,100);
    arms::chassis::move(6, RELATIVE);
    pros::delay(500);
    arms::chassis::move({30,6,-10}, RELATIVE);
    intake::intakeMotor.moveVoltage(12000);
    arms::chassis::move(20);
    pros::delay(1200);
    intake::intakeMotor.moveVoltage(0);


    
}
