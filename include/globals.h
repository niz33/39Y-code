#pragma once
#include "lemlib/chassis/chassis.hpp"
#include "main.h"

//Controller
extern pros::Controller master;

//Grabber
extern pros::ADIDigitalOut pneumatic;

//wheels
extern pros::Motor leftWheel1;
extern pros::Motor leftWheel2;
extern pros::Motor leftWheel3;
extern pros::MotorGroup leftWheels;

extern pros::Motor rightWheel1;
extern pros::Motor rightWheel2;
extern pros::Motor rightWheel3;
extern pros::MotorGroup rightWheels;

//intake
extern pros::Motor intakeMotor;
extern pros::Motor outtakeMotor;
extern pros::Motor sortMotor;
extern pros::Motor midMotor;

extern pros::Optical cSensor;
extern pros::Optical cSensor2;
extern pros::Distance dSensor;

//horizontal odometry
extern pros::Rotation horizontalRotation;
extern pros::Rotation verticalRotation;

extern lemlib::TrackingWheel horizontal_tracking_wheel;
extern lemlib::TrackingWheel vertical_tracking_wheel;

//ladybrown
extern pros::Motor wallStakeMotor;

extern pros::ADIDigitalOut matchLoad;
extern pros::ADIDigitalOut wing;
extern pros::ADIDigitalOut middleDescore;

//Inertia Sensor
extern pros::Imu inertial;

extern pros::Distance distLeft;
extern pros::Distance distRight;
extern pros::Distance distFront;
extern pros::Distance distBack;

// //lemlib
extern lemlib::Drivetrain drivetrain;
extern lemlib::OdomSensors sensors;
extern lemlib::ControllerSettings lateral_controller;
extern lemlib::ControllerSettings angular_controller;
extern lemlib::Chassis chassis;

extern pros::Task printTask;
extern pros::Task intakeTask;