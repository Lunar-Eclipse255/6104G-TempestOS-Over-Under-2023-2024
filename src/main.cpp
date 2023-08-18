#include "main.h"
#include "display.hpp"
#include "autons.hpp"
#define INDEX_PORT 'A'
#define ENDGAME_PORT 'C'







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

//sets up motor groups for the left and right motors
MotorGroup leftChassis ({-1, 1});
MotorGroup rightChassis ({10,-20});

//Digitally Builds the Chassis
std::shared_ptr<ChassisController> drive =
	ChassisControllerBuilder()
		//.withMotors(leftChassis,rightChassis)
		.withMotors(
			leftChassis,
			rightChassis
		)
		// Green gearset, 4 in wheel diam, 11.5 in wheel track
		.withDimensions(AbstractMotor::gearset::green, {{4.125_in, 10_in}, imev5GreenTPR})
		.withGains(
			{0.001},
			{0.1}, //tune
			{0.0001}
		)
		.build();

Motor intakeMotorTwo (2);
Motor intakeMotorOne (-9);




//Runs initialization code. This occurs as soon as the program is started. All other competition modes are blocked by initialize; it is recommended to keep execution time for this mode under a few seconds.
void initialize() {
	//pros::lcd::initialize();
   


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
		drive->getModel()->arcade(controller.getAnalog(ControllerAnalog::leftY),controller.getAnalog(ControllerAnalog::rightX));

		ControllerButton intakeOutButton(ControllerDigital::R2);
		ControllerButton intakeInButton(ControllerDigital::R1);
		//pros::ADIDigitalOut index (INDEX_PORT);
		//pros::ADIDigitalOut endgame (ENDGAME_PORT);
		
		 /*Describe the color for the needles*/
	/*
    static lv_color_t needle_colors[1];
    needle_colors[0] = LV_COLOR_BLUE;

	
    lv_obj_t * gauge1 = lv_gauge_create(lv_scr_act(), NULL);
    lv_gauge_set_needle_count(gauge1, 1, needle_colors);
    lv_obj_set_size(gauge1, 150, 150);
    lv_obj_align(gauge1, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
	
    int batteryPercentage = pros::battery::get_capacity();
    lv_gauge_set_value(gauge1, 0, batteryPercentage); 
	*/
	
		
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