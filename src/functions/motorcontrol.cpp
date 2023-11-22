#include "main.h"
#include "motors.h"
#include "motorcontrol.hpp"
#include <string>
class MotorFunctions{
    public: 
        MotorFunctions(okapi::Motor motorName, okapi::ControllerDigital In, okapi::ControllerDigital Out) {}
        

    /*
        MotorFunctions(Motor motor, okapi::ControllerDigital In, okapi::ControllerDigital Out){
            ControllerButton inButton(In);
            ControllerButton outButton(Out);
            if (inButton.isPressed()) {
                motor.moveVoltage(12000);
            } 
            //else if the intakeOut button is pressed it gives the intake -12000 mV
            else if (outButton.isPressed()) {
                motor.moveVoltage(-12000);
            }
            //else it stops powering the intake motor
            else {
                motor.moveVoltage(0);
            }
        }
        */
};
