#ifndef _PNEUMATICS_HPP_
#define _PNEUMATICS_HPP_

#include "main.h"

extern pros::ADIDigitalOut leftPTO;
extern pros::ADIDigitalOut rightPTO;
extern pros::ADIDigitalOut leftWingCurved;
extern pros::ADIDigitalOut rightWingCurved;
extern pros::ADIDigitalOut leftWingDD;
extern pros::ADIDigitalOut rightWingDD;

namespace pneumatics {
    void init();
    void dropdown();
    void curved();
    void pto();
}

#endif