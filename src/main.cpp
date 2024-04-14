#include "main.h"
#include "display.hpp"
#include "autons.hpp"
#include "motors.h"
#include "gif-pros/gifclass.hpp"
#include "turn_voltage.hpp"
#include "ARMS/config.h"
#include "subsystems/intake.h"
float error;
float prevError=0;
float integral=0;
float setpoint=600.0;
float derivative;
float power=120000;
float kP=3.1;
float kI=0;
float kD=0;
float k = 600.0/12000.0;
int value=0;
//Motor intakeMotor(-19);
//Runs initialization code. This occurs as soon as the program is started. All other competition modes are blocked by initialize; it is recommended to keep execution time for this mode under a few seconds.
void initialize() {
	//pros::lcd::initialize();
	arms::init();
	//initializes sylib
   	sylib::initialize();
	drive::init();
	pneumatics::init();
	intake::init();
	
}

//Runs while the robot is in the disabled state of Field Management System or the VEX Competition Switch, following either autonomous or opcontrol. When the robot is enabled, this task will exit.
void disabled() {
	
}

//Runs after initialize(), and before autonomous when connected to the Field Management System or the VEX Competition Switch. This is intended for competition-specific initialization routines, such as an autonomous selector on the LCD. This task will exit when the robot is enabled and autonomous or opcontrol starts.
void competition_initialize() {
	// Set up LVGL display
	MainLVGL();
}

//Runs the user autonomous code. This function will be started in its own task with the default priority and stack size whenever the robot is enabled via the Field Management System or the VEX Competition Switch in the autonomous mode. Alternatively, this function may be called in initialize or opcontrol for non-competition testing purposes. If the robot is disabled or communications is lost, the autonomous task will be stopped. Re-enabling the robot will restart the task, not re-start it from where it left off.
void autonomous() {
	//initializes the lcd for pros
	//pros::lcd::initialize();
	//runSelectedGIF();
	//runs the selected autonomous/skills program
	//runSelectedAuto();
	rightBlueOneAuton();
	PIDScreen();
	//arms::chassis::move({{24, 0}}, 100, arms::THRU | arms::ASYNC);
	}
	
//Runs the operator control code. This function will be started in its own task with the default priority and stack size whenever the robot is enabled via the Field Management System or the VEX Competition Switch in the operator control mode. If no competition control is connected, this function will run immediately following initialize(). If the robot is disabled or communications is lost, the operator control task will be stopped. Re-enabling the robot will restart the task, not resume it from where it left off.
void opcontrol() {

	ControllerButton shiftKeyButton(ControllerDigital::L1);
    ControllerButton intakeOutButton(ControllerDigital::R2);
    ControllerButton intakeInButton(ControllerDigital::R1);


	pros::Task intake (intake::control);
	pros::Task kicker (kicker::control);
	if ((autoType == AUTONOMOUS_SKILLS)&&(selectedProgram==1)){
		dSkills();
	}
	if (selectedDebugOption==1){ 
		PIDScreen();
	}
	while (true) {
		if (selectedDebugOption==1){ 
			PIDConstantUpdating();
		}
		drive::control();
		pneumatics::dropdown();
		pneumatics::curved();
		pneumatics::hang();

		//pros::screen::set_pen(COLOR_BLUE);
			//pros::screen::print(pros::E_TEXT_MEDIUM, 3, "%d",rightChassis.getActualVelocity());
			pros::delay(10);
	}
}