#include "main.h"
#include "pros/abstract_motor.hpp"

pros::Controller master(pros::E_CONTROLLER_MASTER);


//wheels
pros::Motor leftWheel1(11, pros::v5::MotorGears::blue);
pros::Motor leftWheel2(-12, pros::v5::MotorGears::blue);
pros::Motor leftWheel3(-13, pros::v5::MotorGears::blue);
// pros::MotorGroup leftWheels({-13},pros::v5::MotorGears::blue);
pros::MotorGroup leftWheels({11,-12,-13},pros::v5::MotorGears::blue);

pros::Motor rightWheel1(18,pros::v5::MotorGears::blue);
pros::Motor rightWheel2(17,pros::v5::MotorGears::blue);
pros::Motor rightWheel3(-20,pros::v5::MotorGears::blue);
// pros::MotorGroup rightWheels({16},pros::v5::MotorGears::blue);
pros::MotorGroup rightWheels({18,17,-20},pros::v5::MotorGears::blue); 

//intake
pros::Motor intakeMotor(-14, pros::v5::MotorGears::blue);
pros::Motor outtakeMotor(-15, pros::v5::MotorGears::blue);

pros::Optical cSensor(9);

pros::ADIDigitalOut matchLoad('A', false);
pros::ADIDigitalOut wing('C', false);

 
//inertial Sensor
pros::Imu inertial(16);

//odometry
pros::Rotation horizontalRotation(15);
pros::Rotation verticalRotation(-14);

lemlib::TrackingWheel horizontal_tracking_wheel(&horizontalRotation, lemlib::Omniwheel::NEW_275, 2.65);

lemlib::TrackingWheel vertical_tracking_wheel(&verticalRotation, lemlib::Omniwheel::NEW_275, 0.625);


// lemlib::TrackingWheel horizontal_tracking_wheel(&odomRotation, lemlib::Omniwheel::NEW_2,+2.5);


lemlib::ExpoDriveCurve throttle_curve(3, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                     1.019 // expo curve gain
);

// input curve for steer input during driver control
lemlib::ExpoDriveCurve steer_curve(3, // joystick deadband out of 127
                                  10, // minimum output where drivetrain will move out of 127
                                  1.019 // expo curve gain
);

//lemlib
lemlib::Drivetrain drivetrain(&leftWheels,
                              &rightWheels,
                              11.7, //10.8 inches width
                              lemlib::Omniwheel::NEW_4,
                              300, //drivetrain rpm
                                2 // horizontal drift
);

lemlib::OdomSensors sensors(nullptr, //&vertical_tracking_wheel,
                            nullptr,
                            nullptr,
                            nullptr,
                            &inertial // inertial sensor
);

lemlib::ControllerSettings lateral_controller(
  9, //kP
  0.0, //kI
  10, //kD
  3.0, // anti windup
  1, // small error range in inches
  100, // small error range timeout, in miliseconds
  3, // large error range in inches
  500, // large error range timeout, in miliseconds
  50 // max acceleration (slew)
);
lemlib::ControllerSettings angular_controller(
  2, // proportional gain (kP)
  0.00, // integral gain (kI)
  5, // derivative gain (kD)
  3, // anti windup
  1, // small error range, in degrees
  100, // small error range timeout, in milliseconds
  3, // large error range, in degrees
  500, // large error range timeout, in milliseconds
  0 // maximum acceleration (slew)
);

// create the chassis
lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors, // odometry sensors
                        &throttle_curve, 
                        &steer_curve
);

pros::Task colorSortTask(Autonomous::print);
