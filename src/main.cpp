#include "main.h"
#include "display.hpp"
#include "autons.hpp"
#include "motors.h"
#define WING_LEFT 'B'
#define WING_RIGHT 'C'
#define ARM 'D'



double motorVelocityCalc(double joystickInput) {
	//Coefficients for Cubic model
    double a = 5.0; 
    double b = 1.0; 
	double c = 2.0; 
	double d = 0.0; 
	double e = 0.0; 

    //motorVelocity = ax^4+ bx^3 + cx^2 + dx + e, where x is the joystick value: Quartic Linear regression model
    double motorVelocity = (a * pow(joystickInput, 4)) + (b * pow(joystickInput, 3)) + (c * pow(joystickInput, 2))+ (d * joystickInput)+e;

    //Adjusts value to fit into expected input value 
    motorVelocity = std::min(100.0, std::max(-100.0, motorVelocity));

    //Adds the direction back to the motor power
	if (selectedProfile==0){
    return (joystickInput < 0) ? -motorVelocity : motorVelocity;
	}
	else {
		return (joystickInput < 0) ? motorVelocity : -motorVelocity;
	}

}

double turningValueCalc(double joystickInput) {
    //Coefficients for Quartic model
    double a = 3.0; 
    double b = 1.0; 
	double c = 2.0; 
	double d = 0.0; 
	double e = 0.0; 

    //motorVelocity = ax^4+ bx^3 + cx^2 + dx + e, where x is the joystick value: Quartic Linear regression model
    double turningValue = (a * pow(joystickInput, 3)) + (b * pow(joystickInput, 3)) + (c * pow(joystickInput, 2))+ (d * joystickInput)+e;
    //Adjusts value to fit into expected input value 
    turningValue = std::min(1.0, std::max(-1.0, turningValue));

	//returns the turningValue
	return -turningValue;
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

Motor backLeftDriveMotor (20);
Motor middleLeftDriveMotor (19);
Motor frontLeftDriveMotor (18);
Motor upLeftDriveMotor (-17);
Motor backRightDriveMotor (-10);
Motor middleRightDriveMotor (-9);
Motor frontRightDriveMotor (-8);
Motor upRightDriveMotor (7);
MotorGroup leftChassis ({backLeftDriveMotor,middleLeftDriveMotor,frontLeftDriveMotor, upLeftDriveMotor});
MotorGroup rightChassis ({backRightDriveMotor, middleRightDriveMotor, frontRightDriveMotor, upRightDriveMotor});


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




Motor intakeMotor(16);
Motor catapultMotor (11);
ADIButton catapultLimit ('A');
bool wingCheck;
bool pistonExtended;


//Runs initialization code. This occurs as soon as the program is started. All other competition modes are blocked by initialize; it is recommended to keep execution time for this mode under a few seconds.
void initialize() {
	wingCheck=true;
	pistonExtended = false;

	//pros::lcd::initialize();
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
	pros::lcd::initialize();
	runSelectedAuto();
	}
	
//Runs the operator control code. This function will be started in its own task with the default priority and stack size whenever the robot is enabled via the Field Management System or the VEX Competition Switch in the operator control mode. If no competition control is connected, this function will run immediately following initialize(). If the robot is disabled or communications is lost, the operator control task will be stopped. Re-enabling the robot will restart the task, not resume it from where it left off.
void opcontrol() {
	lv_init();

	

	
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
		ControllerButton catapultProgressionButton(ControllerDigital::L1);
		ControllerButton catapultButtonBack(ControllerDigital::up);
		ControllerButton wingButton(ControllerDigital::Y);
		ControllerButton armButton(ControllerDigital::right);
		pros::ADIDigitalOut leftWing (WING_LEFT);
		pros::ADIDigitalOut rightWing (WING_RIGHT);
		pros::ADIDigitalOut arm (ARM);
		//pros::ADIDigitalIn catapultLimit (CATA_PORT);
		


		//pros::ADIDigitalOut leftWing (INDEX_PORT);
		//pros::ADIDigitalOut endgame (ENDGAME_PORT);
	pros::screen::set_pen(COLOR_BLUE);
    pros::screen::print(pros::E_TEXT_MEDIUM, 3, "%d",rightChassis.getActualVelocity());
	pros::screen::print(pros::E_TEXT_MEDIUM, 3,"%d", leftChassis.getActualVelocity());

		
		
		if (catapultButton.isPressed()) {
			if (catapultProgressionButton.isPressed()){
				catapultMotor.moveVoltage(12000);
			}
			else if (catapultLimit.isPressed()){
				catapultMotor.moveVoltage(0);
			}
			else  {
				catapultMotor.moveVoltage(12000);
			}
		}
		else if (catapultButtonBack.isPressed()) {
        	catapultMotor.moveVoltage(-12000);
		}
		else{
			catapultMotor.moveVoltage(0);
		}
		if (intakeInButton.isPressed()) {
        	intakeMotor.moveVoltage(12000);
    	} 
		else if (intakeOutButton.isPressed()) {
        	intakeMotor.moveVoltage(-12000);
		}
		else {
        	intakeMotor.moveVoltage(0);
    	}
		if (wingButton.isPressed() && !pistonExtended) {
            leftWing.set_value(true); // Extend the piston
            pistonExtended = true; // Set the piston state to extended
        } else if (!wingButton.isPressed() && pistonExtended) {
            // If the button is released and the piston is extended, retract it
            leftWing.set_value(false); // Retract the piston
            pistonExtended = false; // Set the piston state to retracted
        }
		/*
		if (wingButton.isPressed()) {
			//leftWing.set_value(true);
			//rightWing.set_value(true);
			//pros::delay(5000);

    	
		
			
			if (wingCheck==true){
				leftWing.set_value(true);
				rightWing.set_value(true);
				wingCheck=false;
				pros::delay(5000);
			}
			else {
				leftWing.set_value(false);
				rightWing.set_value(false);
				wingCheck=true;
				pros::delay(5000);
			}
		}
		if (armButton.isPressed()) {
			arm.set_value(true);
			pros::delay(5000);
		}	
		*/
	
    	
		
		
		// Wait and give up the time we don't need to other tasks.
		// Additionally, joystick values, motor telemetry, etc. all updates every 10 ms.
		
		pros::delay(10);
		
	}
	
}