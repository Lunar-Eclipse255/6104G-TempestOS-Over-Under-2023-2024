#include "main.h"
#include "display.hpp"
#include "autons.hpp"
#include "motors.h"
#include "gif-pros/gifclass.hpp"
#include "ARMS/config.h"

namespace intake {
    Motor intakeMotor(-19);
    ControllerButton shiftKeyButton(ControllerDigital::L1);
    ControllerButton intakeOutButton(ControllerDigital::R2);
    ControllerButton intakeInButton(ControllerDigital::R1);
    
    void init(){

    }
    void control(){

		
    }
}