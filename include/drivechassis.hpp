#ifndef DRIVECHASSIS_HPP
#define DRIVECHASSIS_HPP

#include "main.h"

class DriveChassis {
public:
    DriveChassis(int motorOneLeft, int motorTwoLeft, int motorThreeLeft, int motorFourLeft, int motorOneRight, int motorTwoRight, int motorThreeRight, int motorFourRight, AbstractMotor::gearset cartridgeColor, double driverGear, double drivenGear, double wheelDiameter, double wheelTrack, double* distance, double* turn, double* angle);
    // Other methods...

private:
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
    okapi::QLength  wheelDiameter;
    okapi::QLength wheelTrack;
    double TPR;
    // Instance variables...
};
extern std::shared_ptr<ChassisController> driveChassis;
#endif // DRIVECHASSIS_HPP