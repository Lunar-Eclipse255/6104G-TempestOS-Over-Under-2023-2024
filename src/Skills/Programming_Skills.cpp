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

    //Add code to get the two alliance triballs
    
    driveChassis->setMaxVelocity(120);
    intakeMotor.moveVoltage(-12000);
	pros::delay(200);
    intakeMotor.moveVoltage(0);
    pros::delay(200);
    leftChassis.moveVoltage(-12000);
    rightChassis.moveVoltage(-6000);
    pros::delay(1000);
    leftChassis.moveVoltage(6000);
    rightChassis.moveVoltage(6000);
    pros::delay(400);
    leftChassis.moveVoltage(-6000);
    rightChassis.moveVoltage(-6000);
    pros::delay(800);
    
    leftChassis.moveVoltage(6000);
    rightChassis.moveVoltage(6000);
    
    pros::delay(800);
    leftChassis.moveVoltage(0);
    rightChassis.moveVoltage(0);
    driveChassis->setMaxVelocity(50);
    driveChassis->turnAngle(-85_deg);
    driveChassis->moveDistance(5_cm);
    //catapultMotor.moveVoltage(-11000);
    //pros::delay(300);
    catapultMotor.moveVoltage(11000);
    //pros::delay(35000);
    pros::delay(850);
    //pros::delay(70000);
    catapultMotor.moveVoltage(0);
    driveChassis->setMaxVelocity(120);
    driveChassis->moveDistance(-10_cm);
    driveChassis->turnAngle(-56_deg); 
    rightChassis.moveVoltage(-11000);
    leftChassis.moveVoltage(-9000);
    pros::delay(1700);
    rightChassis.moveVoltage(0);
    leftChassis.moveVoltage(0);
    rightChassis.moveVoltage(-11000);
    leftChassis.moveVoltage(-3000);
    pros::delay(1300);
    rightChassis.moveVoltage(0);
    leftChassis.moveVoltage(0);
    rightChassis.moveVoltage(-12000);
    leftChassis.moveVoltage(-12000);
    pros::delay(150);
    rightChassis.moveVoltage(0);
    leftChassis.moveVoltage(0);
    pros::delay(500);
    driveChassis->setMaxVelocity(600);
    driveChassis->turnAngle(-145_deg);
    driveChassis->setMaxVelocity(150);
    rightChassis.moveVoltage(0);
    leftChassis.moveVoltage(0);
    driveChassis->setMaxVelocity(80);
    leftWing.set_value(true);
    driveChassis->moveDistance(-80_cm);
    
    rightWing.set_value(true);
    driveChassis->turnAngle(-120_deg);
    intakeMotor.moveVoltage(-0);
    rightChassis.moveVoltage(-12000);
    leftChassis.moveVoltage(-12000);
    pros::delay(800);
    rightChassis.moveVoltage(12000);
    leftChassis.moveVoltage(12000);
    pros::delay(700);
    rightChassis.moveVoltage(0);
    leftChassis.moveVoltage(0);
    driveChassis->turnAngle(-45_deg);
    rightChassis.moveVoltage(-12000);
    leftChassis.moveVoltage(-12000);
    pros::delay(800);
    rightChassis.moveVoltage(12000);
    leftChassis.moveVoltage(12000);
    pros::delay(700);
    driveChassis->turnAngle(75_deg);
    rightChassis.moveVoltage(-12000);
    leftChassis.moveVoltage(-12000);
    pros::delay(800);
    rightChassis.moveVoltage(12000);
    leftChassis.moveVoltage(12000);
    pros::delay(700);
    rightChassis.moveVoltage(0);
    leftChassis.moveVoltage(0);
    
    //driveChassis->moveDistance(-72_cm);
    //driveChassis->turnAngle(-68_deg); //was 75
    /*
    driveChassis->setMaxVelocity(50);
    driveChassis->moveDistance(34_cm);
    catapultMotor.moveVoltage(9000);

    //pros::delay(40000);
    pros::delay(850);
    //pros::delay(80000)
    catapultMotor.moveVoltage(0);
    driveChassis->moveDistance(-6_cm);
    driveChassis->turnAngle(-65_deg);
    driveChassis->setMaxVelocity(120);
    driveChassis->moveDistance(-60_cm);
    driveChassis->turnAngle(31_deg); //30.5
    driveChassis->moveDistance(-130_cm);
    //break
    rightChassis.moveVoltage(-12000);
    leftChassis.moveVoltage(-2500);
    pros::delay(900);
    rightChassis.moveVoltage(-0);
    leftChassis.moveVoltage(0);
    rightChassis.moveVoltage(-8500); //old was -4500
    rightWing.set_value(true);
    leftWing.set_value(true);
    leftChassis.moveVoltage(-12000);
    pros::delay(900);
    
    rightChassis.moveVoltage(-0);
    leftChassis.moveVoltage(0);
    /*
    driveChassis->setMaxVelocity(600);
    driveChassis->moveDistance(-60_cm);
    driveChassis->moveDistance(60_cm);
    driveChassis->turnAngle(25_deg);
    driveChassis->moveDistance(-75_cm);
    driveChassis->moveDistance(70_cm);
    driveChassis->turnAngle(-47_deg);
    driveChassis->moveDistance(-80_cm);
    driveChassis->moveDistance(70_cm);
    */
    

    
    
    
}