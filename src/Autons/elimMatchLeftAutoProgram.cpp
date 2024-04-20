#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"
#include "okapi/api.hpp"
#include "turn_voltage.hpp"
using namespace arms;

void elimMatchLeftAuton(void) {
    intake::init();
    chassis::move(-32.786, -57.248, 5000);
    chassis::move({0, 0,70});
    chassis::move({47, 0,70});
    intake::intakeMotor.moveVoltage(-12000);
    pros::delay(1000);
    chassis::turn(-70);
    intake::intakeMotor.moveVoltage(12000);
    chassis::move({56, 10,-90});
    pros::delay(1000);
    intake::intakeMotor.moveVoltage(0);
    chassis::move({56, 16,-90});
    pneumatics::leftWingCurved.set_value(true);
    chassis::turn(-180);
    chassis::turn(-210);
    pneumatics::leftWingCurved.set_value(false);
    chassis::move({2, -8,-120});
    intake::intakeMotor.moveVoltage(-12000);
    chassis::move({-3,29,-90});


}