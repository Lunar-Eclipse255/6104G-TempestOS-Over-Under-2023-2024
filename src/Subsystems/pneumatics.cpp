#include "main.h"
#include "display.hpp"
#include "autons.hpp"
#include "motors.h"
#include "gif-pros/gifclass.hpp"
#include "ARMS/config.h"

namespace pneumatics {
    #define HANG_ONE 'A'
    #define HANG_TWO 'B'
    #define HANG_THREE 'C'
    #define HANG_FOUR 'D'
    #define WING_LEFT_CURVED 'E'
    #define WING_RIGHT_CURVED 'F'
    #define WING_LEFT_DD 'G'
    #define WING_RIGHT_DD 'H'
    bool wingCheckLeftCurved;
    bool wingCheckRightCurved;
    bool wingCheckLeftDD;
    bool wingCheckRightDD;
    bool hangCheck;
    ControllerButton shiftKeyButton(ControllerDigital::L1);
    ControllerButton HangOutButton(ControllerDigital::up);
    ControllerButton HangInButton(ControllerDigital::X);
    ControllerButton wingOutLeftCurvedButton(ControllerDigital::right);
    ControllerButton wingInLeftCurvedButton(ControllerDigital::left);
    ControllerButton wingOutRightCurvedButton(ControllerDigital::Y);
    ControllerButton wingInRightCurvedButton(ControllerDigital::A);
    ControllerButton wingOutLeftDDButton(ControllerDigital::right);
    ControllerButton wingInLeftDDButton(ControllerDigital::left);
    ControllerButton wingOutRightDDButton(ControllerDigital::Y);
    ControllerButton wingInRightDDButton(ControllerDigital::A);
    pros::ADIDigitalOut hangOne (HANG_ONE);
    pros::ADIDigitalOut hangTwo (HANG_TWO);
    pros::ADIDigitalOut hangThree (HANG_THREE);
    pros::ADIDigitalOut hangFour (HANG_FOUR);
    pros::ADIDigitalOut leftWingCurved (WING_LEFT_CURVED);
    pros::ADIDigitalOut rightWingCurved (WING_RIGHT_CURVED);
    pros::ADIDigitalOut leftWingDD (WING_LEFT_DD);
    pros::ADIDigitalOut rightWingDD (WING_RIGHT_DD);
    void init(){
        
        wingCheckLeftCurved=false;
        wingCheckRightCurved=false;
        wingCheckLeftDD=false;
        wingCheckRightDD=false;
        hangCheck=false;
    }
    void dropdown(){
        if (shiftKeyButton.isPressed()){
            if (wingOutLeftDDButton.isPressed()) {
                if (wingCheckLeftDD==false){
                    leftWingDD.set_value(true);
                    wingCheckLeftDD=true;
                }
            }
            //Else if the wingOutButton is pressed and the wings aren't already in it extends 
            else if (wingInLeftDDButton.isPressed()) {
                if (wingCheckLeftDD){
                    leftWingDD.set_value(false);
                    wingCheckLeftDD=false;
                }
            }
            if (wingOutRightDDButton.isPressed()) {
                if (wingCheckRightDD==false){
                    rightWingDD.set_value(true);
                    wingCheckRightDD=true;
                }
            }
            //Else if the wingOutButton is pressed and the wings aren't already in it extends 
            else if (wingInRightDDButton.isPressed()) {
                if (wingCheckRightDD){
                    rightWingDD.set_value(false);
                    wingCheckRightDD=false;
                }
            }
        }
    }
    void curved(){
        if (!(shiftKeyButton.isPressed())){
            if (wingOutLeftCurvedButton.isPressed()) {
                if (wingCheckLeftCurved==false){
                    leftWingCurved.set_value(true);
                    wingCheckLeftCurved=true;
                }
            }
            //Else if the wingOutButton is pressed and the wings aren't already in it extends 
            else if (wingInLeftCurvedButton.isPressed()) {
                if (wingCheckLeftCurved){
                    leftWingCurved.set_value(false);
                    wingCheckLeftCurved=false;
                }
            }
            if (wingOutRightCurvedButton.isPressed()) {
                if (wingCheckRightCurved==false){
                    rightWingCurved.set_value(true);
                    wingCheckRightCurved=true;
                }
            }
            //Else if the wingOutButton is pressed and the wings aren't already in it extends 
            else if (wingInRightCurvedButton.isPressed()) {
                if (wingCheckRightCurved){
                    rightWingCurved.set_value(false);
                    wingCheckRightCurved=false;
                }
            }
        }
    }
    void hang(){
        if (shiftKeyButton.isPressed()){
            if (HangOutButton.isPressed()){
                if (!hangCheck){
                    hangOne.set_value(true);
                    hangTwo.set_value(true);
                    hangThree.set_value(true);
                    hangFour.set_value(true);
                    hangCheck=true;
                }
            }
            else if (HangInButton.isPressed()){
                if (hangCheck){
                    hangOne.set_value(false);
                    hangTwo.set_value(false);
                    hangThree.set_value(false);
                    hangFour.set_value(false);
                    hangCheck=false;
                }
            }
        }
    }
}