#include "main.h"
#include "motors.h"
#include "motorcontrol.hpp"


MotorControl::MotorControl(int motor, okapi::ControllerDigital In, okapi::ControllerDigital Out){
    ControllerButton inButton(In);
    ControllerButton outButton(Out);
    if (inButton.isPressed()) {
        motorArray[motor].moveVoltage(12000);
    } 
    //else if the intakeOut button is pressed it gives the intake -12000 mV
    else if (outButton.isPressed()) {
        motorArray[motor].moveVoltage(-12000);
    }
    //else it stops powering the intake motor
    else {
        motorArray[motor].moveVoltage(0);
    }
}
