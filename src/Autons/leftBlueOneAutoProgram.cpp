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
    chassis::move(6,100);
    pneumatics::rightWingDD.set_value(true);
    pros::delay(200);
    chassis::turn(180,100);
    intake::intakeMotor.moveVoltage(-12000);
    chassis::move(18,100);
}