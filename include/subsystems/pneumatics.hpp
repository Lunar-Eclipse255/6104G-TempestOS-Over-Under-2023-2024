#ifndef _PNEUMATICS_HPP_
#define _PNEUMATICS_HPP_

#include "main.h"



namespace pneumatics {
    extern pros::ADIDigitalOut leftPTO;
    extern pros::ADIDigitalOut rightPTO;
    extern pros::ADIDigitalOut leftWingCurved;
    extern pros::ADIDigitalOut rightWingCurved;
    extern pros::ADIDigitalOut leftWingDD;
    extern pros::ADIDigitalOut rightWingDD;
    extern pros::ADIDigitalOut winchRelease;
    void init();
    void dropdownLeft();
    void dropdownRight();
    void curvedLeft();
    void curvedRight();
    void pto();
}

#endif