#ifndef DRIVECHASSIS_H
#define DRIVECHASSIS_H

#include "main.h"

class DriveChassis {
public:
    DriveChassis(int motorOneLeft, int motorTwoLeft, int motorThreeLeft, int motorFourLeft, int motorOneRight, int motorTwoRight, int motorThreeRight, int motorFourRight, AbstractMotor::gearset cartridgeColor, double driverGear, double drivenGear, double wheelDiameter, double wheelTrack, double* distance, double* turn, double* angle);
    std::shared_ptr<ChassisController> driveChassis;
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
    int TPR;
    // Instance variables...
};

#endif // DRIVECHASSIS_H