#include "main.h"
#define WING_LEFT 'B'
#define WING_RIGHT 'C'
//declares the motors, chassis, and ADIButton
extern Motor backLeftDriveMotor;
extern Motor middleLeftDriveMotor;
extern Motor frontLeftDriveMotor;
extern Motor backRightDriveMotor;
extern Motor middleRightDriveMotor;
extern Motor frontRightDriveMotor;
extern Motor upRightDriveMotor;
extern Motor upLeftDriveMotor;
extern MotorGroup leftChassis;
extern MotorGroup rightChassis;
extern Motor intakeMotor;
extern Motor catapultMotor;
extern ADIButton catapultLimit;
extern std::shared_ptr<ChassisController> driveChassis;
extern pros::ADIDigitalOut leftWing ();
extern pros::ADIDigitalOut rightWing ();