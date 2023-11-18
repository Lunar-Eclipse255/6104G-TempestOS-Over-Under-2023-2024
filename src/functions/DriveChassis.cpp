#include "main.h"
#include "motors.h"
#include "drivechassis.hpp"
class DriveChassis {
public:
    int motorOneLeft;
    int motorTwoLeft;
    int motorThreeLeft;
    int motorFourLeft;
    int motorOneRight;
    int motorTwoRight;
    int motorThreeRight;
    int motorFourRight;
    double drivenGear;
    double driverGear;
    AbstractMotor::gearset cartridgeColor;
    okapi::QLength wheelDiameter;
    okapi::QLength wheelTrack;
    int TPR;
    DriveChassis(int motorOneLeft, int motorTwoLeft, int motorThreeLeft, int motorFourLeft, int motorOneRight, int motorTwoRight, int motorThreeRight, int motorFourRight, AbstractMotor::gearset cartridgeColor, double driverGear, double drivenGear, double wheelDiameter, double wheelTrack, double* distance, double* turn, double* angle){
        Motor backLeftDriveMotor (motorOneLeft);
        Motor middleLeftDriveMotor (motorTwoLeft);
        Motor frontLeftDriveMotor (motorThreeLeft);
        Motor upLeftDriveMotor (motorFourLeft);
        Motor backRightDriveMotor (motorOneRight);
        Motor middleRightDriveMotor (motorTwoRight);
        Motor frontRightDriveMotor (motorThreeRight);
        Motor upRightDriveMotor (motorFourRight);
        MotorGroup leftChassis ({backLeftDriveMotor,middleLeftDriveMotor,frontLeftDriveMotor, upLeftDriveMotor});
        MotorGroup rightChassis ({backRightDriveMotor, middleRightDriveMotor, frontRightDriveMotor, upRightDriveMotor});
        this->wheelDiameter=wheelDiameter * okapi::inch;
        this->wheelTrack=wheelTrack * okapi::inch;
        if(cartridgeColor==AbstractMotor::gearset::green){
            TPR=imev5GreenTPR;
        }
        else if(cartridgeColor==AbstractMotor::gearset::red){
            TPR=imev5RedTPR;
        }
        if(cartridgeColor==AbstractMotor::gearset::blue){
            TPR=imev5BlueTPR;
        }
        std::shared_ptr<ChassisController> driveChassis =
        ChassisControllerBuilder()
            //.withMotors(leftChassis,rightChassis)
            //Sets which motors to use
            .withMotors(
                rightChassis,
                leftChassis
            )
            
            // Green cartridge, 3.25 in wheel diam, 17 in wheel track, 36:60 gear ratio.
            .withDimensions({cartridgeColor, (drivenGear / driverGear)}, {{this->wheelDiameter, 17.465_in}, TPR})
            .withOdometry() // Use the same scales as the chassis (above)
            .withGains(
                {distance[0], distance[1], distance[2]}, 
                {turn[0], turn[1], turn[2]}, 
                {angle[0], angle[1], angle[2]}
            )
            .build();

    }
};

