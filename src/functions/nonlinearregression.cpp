#include "main.h"
#include "display.hpp"
#include "autons.hpp"
#include "motors.h"
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
    return (joystickInput < 0) ? -motorVelocity*0.85 : motorVelocity*0.85;
	}
	else {
		return (joystickInput < 0) ? motorVelocity*0.85 : -motorVelocity*0.85;
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
	return turningValue;
}