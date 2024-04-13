#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"
#include "okapi/api.hpp"
#include "turn_voltage.hpp"
#include "ARMS/config.h"
using namespace arms;

void rightBlueOneAuton(void) {

    arms::odom::reset({0,0},0);
    intake::intakeMotor.moveVoltage(12000);
    pros::delay(1000);
    intake::intakeMotor.moveVoltage(0);
	arms::chassis::move({32,17,45});
    pros::delay(200);
    pneumatics::rightWingDD.set_value(true);
    pros::delay(500);
    //pneumatics::rightWingDD.set_value(false);
    pros::delay(500);
    arms::chassis::move(-7, RELATIVE|REVERSE);
    pros::delay(500);
    chassis::turn(170,100);
    pros::delay(500);
    arms::chassis::move({30,8,-28.5}, RELATIVE);
    intake::intakeMotor.moveVoltage(-12000);
    arms::chassis::move(23);
    pros::delay(1200);
    intake::intakeMotor.moveVoltage(0);


    
}
