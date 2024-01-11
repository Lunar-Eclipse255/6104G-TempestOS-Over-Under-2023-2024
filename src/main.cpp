
#include "main.h"
#include "display.hpp"
#include "autons.hpp"
#include "motors.h"
#include "gif-pros/gifclass.hpp"
#include "paths.hpp"
#include "lemlib/api.hpp"
//defines adi ports for pistons
#define BLOCKER 'A'
#define WING_LEFT 'B'
#define WING_RIGHT 'C'
#define ARM 'D'



//Declares variables for state checks.
bool wingCheckLeft;
bool armCheck;
bool wingCheckRight;
bool blockerCheck;

// controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

Motor intakeMotor(-5);
Motor catapultMotor (7);
ADIButton catapultLimit ('A');

// drive motors
pros::Motor backLeftDriveMotor(10, pros::E_MOTOR_GEARSET_18); // left front motor. port 12, reversed
pros::Motor middleLeftDriveMotor(9, pros::E_MOTOR_GEARSET_18); // left middle motor. port 11, reversed
pros::Motor frontLeftDriveMotor(8, pros::E_MOTOR_GEARSET_18); // left back motor. port 1, reversed
pros::Motor backRightDriveMotor(-20, pros::E_MOTOR_GEARSET_18); // right front motor. port 2
pros::Motor middleRightDriveMotor(-19, pros::E_MOTOR_GEARSET_18); // right middle motor. port 11
pros::Motor frontRightDriveMotor(-18, pros::E_MOTOR_GEARSET_18); // right back motor. port 13

// motor groups
pros::MotorGroup leftChassis({backLeftDriveMotor, middleLeftDriveMotor, frontLeftDriveMotor}); // left motor group
pros::MotorGroup rightChassis({backRightDriveMotor, middleRightDriveMotor, frontRightDriveMotor}); // right motor group

// Inertial Sensor on port 2
pros::Imu imu(16);

// drivetrain settings
lemlib::Drivetrain drivetrain(&leftChassis, // left motor group
                              &rightChassis, // right motor group
                              17, // 10 inch track width
                              lemlib::Omniwheel::NEW_325, // using new 3.25" omnis
                              333, // drivetrain rpm is 360
                              2 // chase power is 2. If we had traction wheels, it would have been 8
);

// lateral motion controller
lemlib::ControllerSettings linearController(10, // proportional gain (kP)
                                            0, // integral gain (kI)
                                            3, // derivative gain (kD)
                                            3, // anti windup
                                            1, // small error range, in inches
                                            100, // small error range timeout, in milliseconds
                                            3, // large error range, in inches
                                            500, // large error range timeout, in milliseconds
                                            20 // maximum acceleration (slew)
);

// angular motion controller
lemlib::ControllerSettings angularController(2, // proportional gain (kP)
                                             0, // integral gain (kI)
                                             10, // derivative gain (kD)
                                             3, // anti windup
                                             1, // small error range, in degrees
                                             100, // small error range timeout, in milliseconds
                                             3, // large error range, in degrees
                                             500, // large error range timeout, in milliseconds
                                             0 // maximum acceleration (slew)
);

// sensors for odometry
// note that in this example we use internal motor encoders (IMEs), so we don't pass vertical tracking wheels
lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// create the chassis
lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors);

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    pros::lcd::initialize(); // initialize brain screen
    //chassis.calibrate(); // calibrate sensors
    wingCheckLeft=false;
	wingCheckRight=false;
	armCheck=false;
	blockerCheck=false;
	//pros::lcd::initialize();
	//initializes sylib
   	sylib::initialize();
    // the default rate is 50. however, if you need to change the rate, you
    // can do the following.
    // lemlib::bufferedStdout().setRate(...);
    // If you use bluetooth or a wired connection, you will want to have a rate of 10ms

    // for more information on how the formatting for the loggers
    // works, refer to the fmtlib docs
    chassis.setPose(0, 0, 0);
    // thread to for brain screen and position logging
    pros::Task screenTask([&]() {
        lemlib::Pose pose(0, 0, 0);
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            // log position telemetry
            lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());
            // delay to save resources
            pros::delay(50);
        }
    });
}

/**
 * Runs while the robot is disabled
 */
void disabled() {}

/**
 * runs after initialize if the robot is connected to field control
 */
void competition_initialize() {
    MainLVGL();
// get a path used for pure pursuit
// this needs to be put outside a function
    // '.' replaced with "_" to make c++ happy
}
ASSET(leftAWP_txt); 
/**
 * Runs during auto
 *
 * This is an example autonomous routine which demonstrates a lot of the features LemLib has to offer
 */
void autonomous() {
    //chassis.moveToPose(2, 0, 0, 5000);
    chassis.follow(leftAWP_txt, 15, 4000, false);
}

/**
 * Runs in driver control
 */
void opcontrol() {
    // controller
	pros::ADIDigitalOut leftWing (WING_LEFT);
	pros::ADIDigitalOut rightWing (WING_RIGHT);
	pros::ADIDigitalOut arm (ARM);
    pros::ADIDigitalOut blocker (BLOCKER);
    // loop to continuously update motors
    while (true) {

        ControllerButton intakeOutButton(ControllerDigital::R2);
		ControllerButton intakeInButton(ControllerDigital::R1);
		ControllerButton catapultButton(ControllerDigital::L2);
		ControllerButton catapultProgressionButton(ControllerDigital::L1);
		ControllerButton catapultButtonBack(ControllerDigital::up);
		ControllerButton wingOutLeftButton(ControllerDigital::left);
		ControllerButton wingInLeftButton(ControllerDigital::right);
		ControllerButton wingOutRightButton(ControllerDigital::A);
		ControllerButton wingInRightButton(ControllerDigital::Y);
        ControllerButton blockerUpButton(ControllerDigital::down);
		ControllerButton blockerDownButton(ControllerDigital::B);
        

        //pros::ADIDigitalIn catapultLimit (CATA_PORT);


		//pros::ADIDigitalOut leftWing (INDEX_PORT);
		//pros::ADIDigitalOut endgame (ENDGAME_PORT);
	//pros::screen::set_pen(COLOR_BLUE);
    //pros::screen::print(pros::E_TEXT_MEDIUM, 3, "%d",rightChassis.getActualVelocity());
	//pros::screen::print(pros::E_TEXT_MEDIUM, 3,"%d", leftChassis.getActualVelocity());

        // get joystick positions
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        // move the chassis with curvature drive
        chassis.curvature(rightX, leftY);
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
		if (intakeInButton.isPressed()) {
        	intakeMotor.moveVoltage(12000);
    	} 
		//else if the intakeOut button is pressed it gives the intake -12000 mV
		else if (intakeOutButton.isPressed()) {
        	intakeMotor.moveVoltage(-12000);
		}
		//else it stops powering the intake motor
		else {
        	intakeMotor.moveVoltage(0);
    	}
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
        if (blockerUpButton.isPressed()) {
			if (blockerCheck==false){
				blocker.set_value(true);
				blockerCheck=true;
			}
		}
		//Else if the wingOutButton is pressed and the wings aren't already in it extends 
		else if (blockerDownButton.isPressed()) {
			if (blockerCheck){
				blocker.set_value(false);
				blockerCheck=false;
			}
		}
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
        // delay to save resources
        pros::delay(10);
    }
}