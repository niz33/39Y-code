#include "main.h"


//     ||============||
//     || DEPRECATED ||
//     ||============||

void DriveTrain::move_velocity(double left, double right){
    leftWheels.move_velocity(left);
    rightWheels.move_velocity(right);
    if(left==0) stopLeft();
    if(right==0) stopRight();
}

void DriveTrain::move_velocity(double left_and_right){
    leftWheels.move_velocity(left_and_right);
    rightWheels.move_velocity(left_and_right);
}

void DriveTrain::stopLeft(){
    leftWheels.set_brake_mode_all(pros::E_MOTOR_BRAKE_COAST);
    leftWheels.move_velocity(0);
    leftWheels.brake();
}

void DriveTrain::stopRight(){
    rightWheels.set_brake_mode_all(pros::E_MOTOR_BRAKE_COAST);
    rightWheels.move_velocity(0);
    rightWheels.brake();
}
