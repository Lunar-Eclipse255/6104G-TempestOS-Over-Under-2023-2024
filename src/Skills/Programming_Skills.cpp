#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"
#include "okapi/api.hpp"
#define WING_LEFT 'B'
#define WING_RIGHT 'C'
using namespace okapi;
pros::ADIDigitalOut leftWing (WING_LEFT);
pros::ADIDigitalOut rightWing (WING_RIGHT);
void pSkills(void) {
    driveChassis->setMaxVelocity(120);
    intakeMotor.moveVoltage(-12000);
	pros::delay(200);
    intakeMotor.moveVoltage(0);
    pros::delay(200);
    driveChassis->moveDistance(-38_cm);
    driveChassis->turnAngle(-75_deg);
    driveChassis->setMaxVelocity(50);
    driveChassis->moveDistance(34_cm);
    catapultMotor.moveVoltage(9000);
    pros::delay(42000);
    //pros::delay(850);
    catapultMotor.moveVoltage(0);
    driveChassis->moveDistance(-6_cm);
    driveChassis->turnAngle(-65_deg);
    driveChassis->setMaxVelocity(120);
    driveChassis->moveDistance(-58_cm);
    driveChassis->turnAngle(32_deg); //41
    driveChassis->moveDistance(-130_cm);
    rightChassis.moveVoltage(-12000);
    leftChassis.moveVoltage(-2500);
    pros::delay(900);
    rightChassis.moveVoltage(-0);
    leftChassis.moveVoltage(0);
    rightChassis.moveVoltage(-4500);
    rightWing.set_value(true);
    leftWing.set_value(true);
    leftChassis.moveVoltage(-12000);
    pros::delay(1200);
    rightChassis.moveVoltage(-0);
    leftChassis.moveVoltage(0);
    driveChassis->moveDistance(-60_cm);
    driveChassis->setMaxVelocity(600);
    driveChassis->moveDistance(60_cm);
    driveChassis->moveDistance(-60_cm);


    //pros::delay(40000);
    
    /*
    driveChassis->turnAngle(100_deg);
    driveChassis->moveDistance(-60_cm);
    driveChassis->turnAngle(85_deg);
    driveChassis->moveDistance(-44_cm);
    driveChassis->turnAngle(89_deg);
    driveChassis->moveDistance(79_cm);
    driveChassis->turnAngle(89_deg);
    leftWing.set_value(true);
    rightWing.set_value(true);
    driveChassis->setMaxVelocity(600);
    driveChassis->moveDistance(-80_cm);
    driveChassis->moveDistance(80_cm);
    */
    
}