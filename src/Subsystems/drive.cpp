#include "main.h"
#include "display.hpp"
#include "autons.hpp"
#include "motors.h"
#include "gif-pros/gifclass.hpp"
#include "ARMS/config.h"


namespace drive {
    pros::Controller master(pros::E_CONTROLLER_MASTER);

    void init() {
        
    }

    void control() {
        arms::chassis::arcade(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y),master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
    }
}