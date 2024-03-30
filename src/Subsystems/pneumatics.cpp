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
    bool wingCheckLeftCurved;
    bool wingCheckRightCurved;
    bool wingCheckLeftDD;
    bool wingCheckRightDD;
    bool PTOCheck;
    ControllerButton shiftKeyButton(ControllerDigital::L1);
    ControllerButton PTOOutButton(ControllerDigital::up);
    ControllerButton PTOInButton(ControllerDigital::X);
    ControllerButton wingOutLeftCurvedButton(ControllerDigital::right);
    ControllerButton wingInLeftCurvedButton(ControllerDigital::left);
    ControllerButton wingOutRightCurvedButton(ControllerDigital::Y);
    ControllerButton wingInRightCurvedButton(ControllerDigital::A);
    ControllerButton wingOutLeftDDButton(ControllerDigital::right);
    ControllerButton wingInLeftDDButton(ControllerDigital::left);
    ControllerButton wingOutRightDDButton(ControllerDigital::Y);
    ControllerButton wingInRightDDButton(ControllerDigital::A);
    pros::ADIDigitalOut leftPTO (PTO_LEFT);
    pros::ADIDigitalOut rightPTO (PTO_RIGHT);
    pros::ADIDigitalOut leftWingCurved (WING_LEFT_CURVED);
    pros::ADIDigitalOut rightWingCurved (WING_RIGHT_CURVED);
    pros::ADIDigitalOut leftWingDD (WING_LEFT_DD);
    pros::ADIDigitalOut rightWingDD (WING_RIGHT_DD);

    void init(){
        wingCheckLeftCurved=false;
        wingCheckRightCurved=false;
        wingCheckLeftDD=false;
        wingCheckRightDD=false;
        PTOCheck=false;
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
    void pto(){
        if (shiftKeyButton.isPressed()){
            if (PTOOutButton.isPressed()){
                if (!PTOCheck){
                    leftPTO.set_value(true);
                    rightPTO.set_value(true);
                    PTOCheck=true;
                }
            }
            else if (PTOInButton.isPressed()){
                if (PTOCheck){
                    leftPTO.set_value(false);
                    rightPTO.set_value(false);
                    PTOCheck=false;
                }
            }
        }
    }
}