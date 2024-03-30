#ifndef _DRIVE_HPP_
#define _DRIVE_HPP_

#include "main.h"

namespace drive {
extern pros::Controller master;
extern pros::MotorGroup left_motors;
extern pros::MotorGroup right_motors;
void init();
void control();
}  

#endif