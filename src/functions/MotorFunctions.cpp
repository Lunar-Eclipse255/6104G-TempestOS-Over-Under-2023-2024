#include "main.h"
#include "motors.h"
#include "motorfunctions.hpp"

class MotorFunctions{
    public: 
        MotorFunctions(okapi::Motor &motor, okapi::ControllerDigital In, okapi::ControllerDigital Out){
           okapi::Motor motor = motor;
        }

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