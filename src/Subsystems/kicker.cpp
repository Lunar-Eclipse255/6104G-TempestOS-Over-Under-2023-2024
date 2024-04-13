#include "main.h"
#include "display.hpp"
#include "autons.hpp"
#include "motors.h"
#include "gif-pros/gifclass.hpp"
#include "ARMS/config.h"

namespace kicker {
    bool kickerToggle = false;
     ControllerButton shiftKeyButton(ControllerDigital::L1);
     ControllerButton kickerToggleButton(ControllerDigital::L2);
     ControllerButton kickerPressButton(ControllerDigital::L2);
     Motor kickerMotor(-3);
    void init(){
        
    }
    void control(){
        while (true){
            if (shiftKeyButton.isPressed()){
                //if the kickerPress button is pressed it gives the kicker 12000 mV
                if (kickerPressButton.isPressed()) {
                    kickerMotor.moveVoltage(12000);
                }
                //else it stops powering the kicker motor
                else {
                    kickerMotor.moveVoltage(0);
                }
            }
            else if (!(shiftKeyButton.isPressed())){
                if (kickerToggleButton.isPressed()) {
                    if (!kickerToggle){
                        kickerMotor.moveVoltage(12000);
                        kickerToggle=true;
                        pros::delay(500);
                    }
                    else{ 
                        kickerMotor.moveVoltage(0);
                        kickerToggle=false;
                        pros::delay(500);
                    }
                } 
            }
        }
    }
}