#include "main.h"
#include "display.hpp"
#include "autons.hpp"
#include "motors.h"
#include "gif-pros/gifclass.hpp"
#include "ARMS/config.h"

namespace intake {
    
    ControllerButton shiftKeyButton(ControllerDigital::L1);
    ControllerButton intakeOutButton(ControllerDigital::R2);
    ControllerButton intakeInButton(ControllerDigital::R1);
    Motor intakeMotor(-13);
    void init(){
        arms::odom::reset({0,0},0);
        intake::intakeMotor.moveVoltage(-12000);
        pros::delay(1000);
        intake::intakeMotor.moveVoltage(0);
    }
    void control(){
        while (true){
            if (!(shiftKeyButton.isPressed())){

                //if the intakeIn button is pressed it gives the intake 12000 mV
                if (intakeInButton.isPressed()) {
                    intakeMotor.moveVoltage(12000);
                } 
                //else if the intakeOut button is pressed it gives the intake -12000 mV
                else if (intakeOutButton.isPressed()) {
                    intakeMotor.moveVoltage(-12000);
                }
                //else it stops powering the intake motor
                else {
                    intakeMotor.moveVoltage(0);
                }
            }
        }
    }
}