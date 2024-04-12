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
    void init();
    void dropdown();
    void curved();
    void pto();
}

#endif