#include "main.h"
#include "display.hpp"
#include "autons.hpp"
#include "motors.h"
#include "gif-pros/gifclass.hpp"
#include "ARMS/config.h"

namespace pneumatics {
    #define PTO_LEFT 'A'
    #define PTO_RIGHT 'B'
    #define WING_LEFT_CURVED 'C'
    #define WING_RIGHT_CURVED 'D'
    #define WING_LEFT_DD 'E'
    #define WING_RIGHT_DD 'F'
    #define WINCH_RELEASE 'G'
    bool wingCheckLeftCurved;
    bool wingCheckRightCurved;
    bool wingCheckLeftDD;
    bool wingCheckRightDD;
    bool PTOCheck;
    bool winchReleaseCheck;
    ControllerButton shiftKeyButton(ControllerDigital::L1);
    ControllerButton PTOButton(ControllerDigital::up);
    ControllerButton winchReleaseDoubleClickButton(ControllerDigital::X);
    ControllerButton winchReleaseSingleClickButton(ControllerDigital::B);
    ControllerButton wingOutLeftCurvedButton(ControllerDigital::right);
    ControllerButton wingLeftCurvedButton(ControllerDigital::left);
    ControllerButton wingRightCurvedButton(ControllerDigital::A);
    ControllerButton wingLeftDDButton(ControllerDigital::right);
    ControllerButton wingRightDDButton(ControllerDigital::Y);
    pros::ADIDigitalOut leftPTO (PTO_LEFT);
    pros::ADIDigitalOut rightPTO (PTO_RIGHT);
    pros::ADIDigitalOut leftWingCurved (WING_LEFT_CURVED);
    pros::ADIDigitalOut rightWingCurved (WING_RIGHT_CURVED);
    pros::ADIDigitalOut leftWingDD (WING_LEFT_DD);
    pros::ADIDigitalOut rightWingDD (WING_RIGHT_DD);
    pros::ADIDigitalOut winchRelease (WINCH_RELEASE);
    void init(){
        wingCheckLeftCurved=false;
        wingCheckRightCurved=false;
        wingCheckLeftDD=false;
        wingCheckRightDD=false;
        PTOCheck=false;
        winchReleaseCheck=false;
    }
    void dropdownLeft(){
        while (true){
            if (wingLeftDDButton.isPressed()) {
                if (wingCheckLeftDD==false){
                    leftWingDD.set_value(true);
                    wingCheckLeftDD=true;
                    pros::delay(500);
                }
                else{
                    leftWingDD.set_value(false);
                    wingCheckLeftDD=false;
                    pros::delay(500);
                }
            }
        }
    }
    void dropdownRight(){
        while (true){
            //If the wingOutButton is pressed and the wings aren't already in it extends 
            if (wingRightDDButton.isPressed()) {
                if (!wingCheckRightDD){
                    rightWingDD.set_value(true);
                    wingCheckRightDD=true;
                    pros::delay(500);
                }
                else {
                    rightWingDD.set_value(false);
                    wingCheckRightDD=false;
                    pros::delay(500);
                }
            }
        }
    }
    void curvedLeft(){
        while (true){
            if (wingLeftCurvedButton.isPressed()) {
                if (wingCheckLeftCurved==false){
                    leftWingCurved.set_value(true);
                    wingCheckLeftCurved=true;
                    pros::delay(500);
                }
                else{
                    leftWingCurved.set_value(false);
                    wingCheckLeftCurved=false;
                    pros::delay(500);
                }
            }
        }
    }
    void curvedRight(){
        while (true){
            if (wingRightCurvedButton.isPressed()) {
                if (wingCheckRightCurved==false){
                    rightWingCurved.set_value(true);
                    wingCheckRightCurved=true;
                    pros::delay(500);
                }
                else{
                    rightWingCurved.set_value(false);
                    wingCheckRightCurved=false;
                    pros::delay(500);
                }
            }
        }
    }
    void pto(){
        while (true){
            if (shiftKeyButton.isPressed()){
                if (PTOButton.isPressed()){
                    if (!PTOCheck){
                        leftPTO.set_value(true);
                        rightPTO.set_value(true);
                        PTOCheck=true;
                        pros::delay(500);
                    }
                    else{
                        leftPTO.set_value(false);
                        rightPTO.set_value(false);
                        PTOCheck=false;
                        pros::delay(500);
                    }
                }
                if (winchReleaseSingleClickButton.isPressed()){
                    if (!winchReleaseCheck){
                        winchRelease.set_value(true);
                        winchReleaseCheck=true;
                        pros::delay(500);
                    }
                    else{
                        winchRelease.set_value(false);
                        winchReleaseCheck=false;
                        pros::delay(500);
                    }
                }
                else if (winchReleaseDoubleClickButton.isPressed()){
                    winchRelease.set_value(true);
                    pros::delay(500);
                    winchRelease.set_value(false);
                    pros::delay(500);
                }
                
            }
        }
    }
}