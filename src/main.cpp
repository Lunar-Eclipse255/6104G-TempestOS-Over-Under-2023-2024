#include "main.h"
#include "display.hpp"
#include "autons.hpp"
#include "motors.h"
#include "gif-pros/gifclass.hpp"
#include "drivechassis.hpp"
#include "motorcontrol.hpp"
#include "nonlinearregression.hpp"
//defines adi ports for pistons
#define WING_LEFT 'B'
#define WING_RIGHT 'C'
#define ARM 'D'


auto cataDistance = DistanceSensor(12);

double PIDDistance[3] = {0.001, 0, 0.0001};
double PIDTurn[3] = {0.001, 0, 0.0001};
double PIDAngle[3] = {0.001, 0, 0.0001};
DriveChassis myChassis(20, 19, 18, -17, -10, -9, -8, 7, AbstractMotor::gearset::green, 60.0, 36.0, 3.25, 17.465, PIDDistance, PIDTurn, PIDAngle);

//Initializes the subsytem motors as well as the Adi Button

Motor intakeMotor(16);
Motor catapultMotor (11);
Motor motorArray[] = {intakeMotor, catapultMotor};
ADIButton catapultLimit ('A');

//Declares variables for state checks.
bool wingCheckLeft;
bool armCheck;
bool wingCheckRight;

//Runs initialization code. This occurs as soon as the program is started. All other competition modes are blocked by initialize; it is recommended to keep execution time for this mode under a few seconds.
void initialize() {
	//initializers the check varibles to false
	wingCheckLeft=false;
	wingCheckRight=false;
	armCheck = false;

	//pros::lcd::initialize();
	//initializes sylib
   	sylib::initialize();
	//Digitally Builds the Chassis
	
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
	pros::lcd::initialize();
	//runs the selected autonomous/skills program
	runSelectedAuto();
	//leftBlueOneAuton();
	}
	
//Runs the operator control code. This function will be started in its own task with the default priority and stack size whenever the robot is enabled via the Field Management System or the VEX Competition Switch in the operator control mode. If no competition control is connected, this function will run immediately following initialize(). If the robot is disabled or communications is lost, the operator control task will be stopped. Re-enabling the robot will restart the task, not resume it from where it left off.
void opcontrol() {
	//clears screen
	//lv_init();
	//Testing: MainLVGL();
	

	
	// Joystick to read analog values for tank or arcade control.
	// Master controller by default.
	//initializes controller and pistons                                                                        
	Controller controller;
	pros::ADIDigitalOut leftWing (WING_LEFT);
	pros::ADIDigitalOut rightWing (WING_RIGHT);
	pros::ADIDigitalOut arm (ARM);
	
	 

	while (true) {
		// Reads joystick input for left/right motion on the right stick
		double joysticTurning = controller.getAnalog(ControllerAnalog::rightX);

        // Calculate turning behavior using the regression model
        double turningValue = turningValueCalc(joysticTurning);

       // Reads joystick input for up/down motion on the left stick
        double joysticMotion = controller.getAnalog(ControllerAnalog::leftY);

        // Calculate motor power using the regression model
        double motorVelocity = motorVelocityCalc(joysticMotion);

       //Uses these new values to control the bot
        driveChassis->getModel()->arcade(motorVelocity, controller.getAnalog(ControllerAnalog::rightX));
		//drive->getModel()->arcade(controller.getAnalog(ControllerAnalog::leftY),controller.getAnalog(ControllerAnalog::rightX));

		//Initializes all the controller buttons
		ControllerButton intakeOutButton(ControllerDigital::R2);
		ControllerButton intakeInButton(ControllerDigital::R1);
		ControllerButton catapultButton(ControllerDigital::L2);
		ControllerButton catapultProgressionButton(ControllerDigital::L1);
		ControllerButton catapultButtonBack(ControllerDigital::up);
		ControllerButton wingOutLeftButton(ControllerDigital::left);
		ControllerButton wingInLeftButton(ControllerDigital::right);
		ControllerButton wingOutRightButton(ControllerDigital::A);
		ControllerButton wingInRightButton(ControllerDigital::Y);
		/*
		ControllerButton ratchetLockOn(ControllerDigital::X);
		ControllerButton ratchetLockOff(ControllerDigital::B);
		//ControllerButton armOutButton(ControllerDigital::A);
		//ControllerButton armInButton(ControllerDigital::left);
		*/
		
		//pros::ADIDigitalIn catapultLimit (CATA_PORT);


		//pros::ADIDigitalOut leftWing (INDEX_PORT);
		//pros::ADIDigitalOut endgame (ENDGAME_PORT);
	//pros::screen::set_pen(COLOR_BLUE);
    //pros::screen::print(pros::E_TEXT_MEDIUM, 3, "%d",rightChassis.getActualVelocity());
	//pros::screen::print(pros::E_TEXT_MEDIUM, 3,"%d", leftChassis.getActualVelocity());

		
		//Checks if the button for catapult is pressed
		if (catapultButton.isPressed()) {
			//Checks if the button for catapult progression is pressed, if so gives the catapultMotor 12000 mV
			if (catapultProgressionButton.isPressed()){
				catapultMotor.moveVoltage(12000);
			}
			//if the catapult limit switch is pressed it stops the motor
			else if (catapultLimit.isPressed()){
				catapultMotor.moveVoltage(0);
			}
			else  {
				//else the motor is given 12000 mV
				catapultMotor.moveVoltage(12000);
			}
		} //else if the catapult back button it gives -12000 mV
		else if (catapultButtonBack.isPressed()) {
        	catapultMotor.moveVoltage(-12000);
		}
		//else its stops powering the motor
		else{
			catapultMotor.moveVoltage(0);
		}
		//if the intakeIn button is pressed it gives the intake 12000 mV
		//MotorControl intakeControl(1, intakeInButton, intakeOutButton);
		
		//If the wingOutButton is pressed and the wings aren't already out it extends 
		if (wingOutLeftButton.isPressed()) {
			if (wingCheckLeft==false){
				leftWing.set_value(true);
				wingCheckLeft=true;
			}
		}
		//Else if the wingOutButton is pressed and the wings aren't already in it extends 
		else if (wingInLeftButton.isPressed()) {
			if (wingCheckLeft){
				leftWing.set_value(false);
				wingCheckLeft=false;
			}
		}
		if (wingOutRightButton.isPressed()) {
			if (wingCheckRight==false){
				rightWing.set_value(true);
				wingCheckRight=true;
			}
		}
		//Else if the wingOutButton is pressed and the wings aren't already in it extends 
		else if (wingInRightButton.isPressed()) {
			if (wingCheckRight){
				rightWing.set_value(false);
				wingCheckRight=false;
			}
		}
		/*
		if (cataDistance.get()>100){
			catapultMotor.moveVoltage(12000);
		}
		else{
			catapultMotor.moveVoltage(12000);
		}
		*/
		/*
		if (armOutButton.isPressed()) {
			if (armCheck==false){
				arm.set_value(true);
				arm.set_value(true);
				armCheck=true;
			}

		}	
		else if (armInButton.isPressed()) {
			if (armCheck){
				arm.set_value(false);
				arm.set_value(false);
				armCheck=false;
			}
		}
		*/
	
    	
		
		
		// Wait and give up the time we don't need to other tasks.
		// Additionally, joystick values, motor telemetry, etc. all updates every 10 ms.
		
		pros::delay(10);
		
	}
	
}