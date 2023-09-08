#include "main.h"
#include "display.hpp"
#include "autons.hpp"
//#define INDEX_PORT 'A'
//#define ENDGAME_PORT 'C'







//A callback function for LLEMU's center button. When this callback is fired, it will toggle line 2 of the LCD text between "I was pressed!" and nothing. 
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}



MotorGroup rightChassis ({1, 2, 11});
MotorGroup leftChassis ({-10 ,-9, -20});

//Digitally Builds the Chassis
std::shared_ptr<ChassisController> drive =
	ChassisControllerBuilder()
		//.withMotors(leftChassis,rightChassis)
		.withMotors(
			rightChassis,
			leftChassis

		)
		// Green gearset, 4 in wheel diam, 11.5 in wheel track
		.withDimensions({AbstractMotor::gearset::green, (36.0 / 60.0)}, {{3.25_in, 17.465_in}, imev5GreenTPR})
    	.withOdometry() // Use the same scales as the chassis (above)
		.withGains(
			{0.001, 0, 0.0001}, // Distance controller gains
        	{0.001, 0, 0.0001}, // Turn controller gains
        	{0.001, 0, 0.0001}  // Angle controller gains (helps drive straight)
		)
		.build();

Motor intakeMotorTwo (12);
Motor intakeMotorOne (-19);
Motor catapultMotor (3);
ADIButton catapultLimit ('A');



//Runs initialization code. This occurs as soon as the program is started. All other competition modes are blocked by initialize; it is recommended to keep execution time for this mode under a few seconds.
void initialize() {
	//pros::lcd::initialize();
   	sylib::initialize();


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
	pros::lcd::initialize();
	runSelectedAuto();
	}
	
//Runs the operator control code. This function will be started in its own task with the default priority and stack size whenever the robot is enabled via the Field Management System or the VEX Competition Switch in the operator control mode. If no competition control is connected, this function will run immediately following initialize(). If the robot is disabled or communications is lost, the operator control task will be stopped. Re-enabling the robot will restart the task, not resume it from where it left off.
void opcontrol() {
	lv_init();
	if (selectedProfile==0){
		pros::screen::set_pen(COLOR_BLUE);
    	pros::screen::print(pros::E_TEXT_MEDIUM, 3, "Gaston");
	} 
	else if (selectedProfile==1){
		pros::screen::set_pen(COLOR_BLUE);
    	pros::screen::print(pros::E_TEXT_MEDIUM, 3, "Patrick");
	}

	
	// Joystick to read analog values for tank or arcade control.
	// Master controller by default.                                                                        
	Controller controller;

	while (true) {
		// Arcade drive with the left stick.
		double leftJoystickInput = controller.getAnalog(okapi::ControllerAnalog::leftY);
		double rightJoystickInput = controller.getAnalog(okapi::ControllerAnalog::rightY);

		double leftScaledValue = pow(leftJoystickInput, 3);   
		double rightScaledValue = pow(rightJoystickInput, 3); 
		leftChassis.moveVoltage(leftScaledValue * 12000);   
		rightChassis.moveVoltage(rightScaledValue * 12000); 
		drive->getModel()->arcade(leftChassis.getVoltage(), rightChassis.getVoltage());






		ControllerButton intakeOutButton(ControllerDigital::R2);
		ControllerButton intakeInButton(ControllerDigital::R1);
		ControllerButton catapultButton(ControllerDigital::L2);
		ControllerButton catapultButtonBack(ControllerDigital::up);

		//pros::ADIDigitalOut index (INDEX_PORT);
		//pros::ADIDigitalOut endgame (ENDGAME_PORT);
		
	pros::lcd::clear_line(3);
	double drivetrainVelocity = rightChassis.getActualVelocity();

    // Print the drivetrain velocity to the PROS terminal (or LCD screen)
    pros::screen::set_pen(COLOR_RED);
    pros::screen::print(pros::E_TEXT_MEDIUM, 1, "%d", drivetrainVelocity);
        // Print the motor velocity to the controller's display on line 3
	if (catapultLimit.isPressed()) {
    	catapultMotor.moveVelocity(0);
		pros::delay(1000);
		catapultMotor.moveVelocity(12000);
	}
	else {
		if (catapultButton.isPressed()) {
        	catapultMotor.moveVoltage(12000);
    	} 
		else if (catapultButtonBack.isPressed()) {
        	catapultMotor.moveVoltage(-12000);
		}
		else {
        	catapultMotor.moveVoltage(0);
    	}
	}
		if (intakeOutButton.isPressed()) {
        	intakeMotorOne.moveVoltage(12000);
			intakeMotorTwo.moveVoltage(12000);
    	} 

		else if (intakeInButton.isPressed()) {
        	intakeMotorOne.moveVoltage(-12000);
			intakeMotorTwo.moveVoltage(-12000);
   		} 

		else {
        	intakeMotorOne.moveVoltage(0);
			intakeMotorTwo.moveVoltage(0);
    	}
		
		
		// Wait and give up the time we don't need to other tasks.
		// Additionally, joystick values, motor telemetry, etc. all updates every 10 ms.
		
		pros::delay(10);
	
	}
	
}