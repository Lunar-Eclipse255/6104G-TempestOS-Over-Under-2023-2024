#include "main.h"
#include "display.hpp"
#include "autons.hpp"
#include "motors.h"
#include "gif-pros/gifclass.hpp"
#include "ARMS/config.h"


double calculate_curves(double x, double t) {
    double y =
        (exp(-t / 10.0) + exp((abs(x) - 127) / 10.0) * (1 - exp(-t / 10.0))) * x;

    return y;
}

void drive_curves_arcade(double forward, double turn) {
    const double forward_t = 4.3;
    const double turn_t = 2.1;

    double forward_curve = calculate_curves(forward, forward_t);
    double turn_curve = calculate_curves(turn, turn_t);

    double left = forward_curve + turn_curve;
    double right = forward_curve - turn_curve;

    drive::left_motors.move_velocity(left);
    drive::right_motors.move_velocity(right);
}
namespace drive {
    pros::Motor L1 = pros::Motor(-10, pros::E_MOTOR_GEARSET_06);
    pros::Motor L2 = pros::Motor(-20, pros::E_MOTOR_GEARSET_06);
    pros::Motor L3 = pros::Motor(-9, pros::E_MOTOR_GEARSET_06);
    pros::Motor R1 = pros::Motor(1, pros::E_MOTOR_GEARSET_06);
    pros::Motor R2 = pros::Motor(11, pros::E_MOTOR_GEARSET_06);
    pros::Motor R3 = pros::Motor(2, pros::E_MOTOR_GEARSET_06);
    pros::IMU imu_sensor(6);

    pros::MotorGroup left_motors({L1, L2, L3});
    pros::MotorGroup right_motors({R1, R2, R3});
    pros::Controller master(pros::E_CONTROLLER_MASTER);

    void init() {
        //imu_sensor.reset();
        //imu_sensor.set_heading(90);
    }

    void control() {
        //drive_curves_arcade(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
        arms::chassis::arcade(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y),master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
    }
}