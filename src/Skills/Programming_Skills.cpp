#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"
#include "okapi/api.hpp"
#include "turn_voltage.hpp"
using namespace okapi;
#define WING_LEFT_DD 'C'
#define WING_RIGHT_DD 'D'
pros::ADIDigitalOut leftWingDD (WING_LEFT_DD);
pros::ADIDigitalOut rightWingDD (WING_RIGHT_DD);

void pSkills(void) {
    
}