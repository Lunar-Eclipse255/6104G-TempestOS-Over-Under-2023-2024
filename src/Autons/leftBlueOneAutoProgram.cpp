#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"
#include "okapi/api.hpp"
#include "turn_voltage.hpp"
#include "ARMS/config.h"
using namespace okapi;
using namespace arms;

void leftBlueOneAuton(void) {
    intake::init();
    chassis::move(12,100);
    if (odom::getLeftEncoder()<20||odom::getRightEncoder()<20){
        while (true){

        }
    }
    pneumatics::rightWingDD.set_value(true);
    pneumatics::leftWingDD.set_value(true);
    pros::delay(200);
    chassis::turn(170,100,REVERSE|RELATIVE);
    chassis::turn(30,100, RELATIVE);
    pneumatics::rightWingDD.set_value(false);
    pneumatics::leftWingDD.set_value(false);
    pros::delay(500);
    intake::intakeMotor.moveVoltage(-12000);
    chassis::move(30,100, RELATIVE);
}