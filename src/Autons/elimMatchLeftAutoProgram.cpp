#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"
#include "okapi/api.hpp"
#include "turn_voltage.hpp"
#include "subsystems/pneumatics.hpp"

using namespace okapi;

void elimMatchLeftAuton(void) {
    pneumatics::leftPTO.set_value(true);
}