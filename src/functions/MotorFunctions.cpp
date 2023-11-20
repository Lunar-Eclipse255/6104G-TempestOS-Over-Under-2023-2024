#include "main.h"
#include "motors.h"
#include "motorfunctions.hpp"

class MotorFunctions{
    public: 
        MotorFunctions(int motorNum, okapi::Motor motorName, okapi::ControllerDigital In, okapi::ControllerDigital Out)
           : motorName(motorNum) {}
        

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