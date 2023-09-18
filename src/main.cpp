#include "main.h"
#include "display.hpp"
#include "autons.hpp"
#include "motors.h"
#define INDEX_PORT 'B'
//#define ENDGAME_PORT 'C'



double motorVelocityCalc(double joystickInput) {
	//Coefficients for Cubic model
    double a = 1.0; 
    double b = 0.0; 
    double c = 0.0; 
	double d = 0.0; 

	//Original value for pow is 2
	//Maybe remove the absolute value
	//motorVelocity = ax^3 + bx^2 + cx +d, where x is the absolute value of the joystick value: Cubic Linear regression model
    double motorVelocity = (a * pow(fabs(joystickInput), 3)) + (b * pow(fabs(joystickInput), 2)) + (c * fabs(joystickInput)) + c;

    //Adjusts value to fit into expected input value 
    motorVelocity = std::min(100.0, std::max(-100.0, motorVelocity));

    //Adds the direction back to the motor power
    return (joystickInput < 0) ? -motorVelocity : motorVelocity;
}

double turningValueCalc(double joystickInput) {
    //Coefficients for Quartic model
    double a = 1.0; 
    double b = 0.0; 
	double c = 0.0; 
	double d = 0.0; 
	double e = 0.0; 

    //motorVelocity = ax^4+ bx^3 + cx^2 + dx + e, where x is the joystick value: Quartic Linear regression model
    double turningValue = (a * pow(joystickInput, 4)) + (b * pow(joystickInput, 3)) + (c * pow(joystickInput, 2))+ (d * joystickInput)+e;

    //Adjusts value to fit into expected input value 
    turningValue = std::min(1.0, std::max(-1.0, turningValue));

	//returns the turningValue
    return turningValue;
}

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


Motor backLeftDriveMotor (-10);
Motor middleLeftDriveMotor (-9);
Motor frontLeftDriveMotor (-20);
Motor backRightDriveMotor (1);
Motor middleRightDriveMotor (2);
Motor frontRightDriveMotor (11);
MotorGroup leftChassis ({backLeftDriveMotor,middleLeftDriveMotor,frontLeftDriveMotor});
MotorGroup rightChassis ({backRightDriveMotor, middleRightDriveMotor, frontRightDriveMotor});

//Digitally Builds the Chassis
std::shared_ptr<ChassisController> drive =
	ChassisControllerBuilder()
		//.withMotors(leftChassis,rightChassis)
		.withMotors(
			leftChassis,
			rightChassis
		)
		// Green gearset, 4 in wheel diam, 11.5 in wheel track
		.withDimensions({AbstractMotor::gearset::green, (60.0 / 36.0)}, {{3.25_in, 17.465_in}, imev5GreenTPR})
    	/*.withOdometry() // Use the same scales as the chassis (above)
		.withGains(
			{0.001, 0, 0.0001}, // Distance controller gains
        	{0.001, 0, 0.0001}, // Turn controller gains
        	{0.001, 0, 0.0001}  // Angle controller gains (helps drive straight)
		) */
		.build();

Motor intakeMotorTwo (4);
Motor intakeMotorOne (-8);
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
		double joysticTurning = controller.getAnalog(ControllerAnalog::rightX);

        // Calculate turning behavior using the regression model
        double turningValue = turningValueCalc(joysticTurning);

        // Read joystick input for forward/backward motion (left joystick's Y-axis)
        double joysticMotion = controller.getAnalog(ControllerAnalog::leftY);

        // Calculate motor power using the quadratic regression model for motion
        double motorVelocity = motorVelocityCalc(joysticMotion);

        // Apply the calculated turning behavior and motor power to control the robot
        drive->getModel()->arcade(motorVelocity, turningValue);
		//drive->getModel()->arcade(controller.getAnalog(ControllerAnalog::leftY),controller.getAnalog(ControllerAnalog::rightX));

		ControllerButton intakeOutButton(ControllerDigital::R2);
		ControllerButton intakeInButton(ControllerDigital::R1);
		ControllerButton catapultButton(ControllerDigital::L2);
		ControllerButton catapultButtonBack(ControllerDigital::up);
		ControllerButton indexCloseThreeButton(ControllerDigital::Y);

		pros::ADIDigitalOut index (INDEX_PORT);
		//pros::ADIDigitalOut endgame (ENDGAME_PORT);
	pros::screen::set_pen(COLOR_BLUE);
    pros::screen::print(pros::E_TEXT_MEDIUM, 3, "%d",rightChassis.getActualVelocity());
	pros::screen::print(pros::E_TEXT_MEDIUM, 3,"%d", leftChassis.getActualVelocity());
	if (catapultLimit.isPressed()) {
    	catapultMotor.moveVelocity(0);
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
		if (indexCloseThreeButton.isPressed()) {
			pros::delay(3000);
			index.set_value(true);
			pros::delay(500);
			index.set_value(false);
			pros::delay(500);
			index.set_value(true);
			pros::delay(500);
			index.set_value(false);
			pros::delay(500);
			index.set_value(true);
			pros::delay(500);
			index.set_value(false);
			pros::delay(500);
    	} 
		
		
		// Wait and give up the time we don't need to other tasks.
		// Additionally, joystick values, motor telemetry, etc. all updates every 10 ms.
		
		pros::delay(10);
	
	}
	
}