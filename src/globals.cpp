#include "main.h"
#include "pros/abstract_motor.hpp"
#include "pros/distance.hpp"

pros::Controller master(pros::E_CONTROLLER_MASTER);


//wheels
pros::Motor leftWheel1(11, pros::v5::MotorGears::blue);
pros::Motor leftWheel2(-12, pros::v5::MotorGears::blue);
pros::Motor leftWheel3(-13, pros::v5::MotorGears::blue);
pros::MotorGroup leftWheels({18,-19,-20},pros::v5::MotorGears::blue);

pros::Motor rightWheel1(18,pros::v5::MotorGears::blue);
pros::Motor rightWheel2(17,pros::v5::MotorGears::blue);
pros::Motor rightWheel3(-20,pros::v5::MotorGears::blue);
pros::MotorGroup rightWheels({11,12,-13},pros::v5::MotorGears::blue); 

//intake
pros::Motor intakeMotor(-2, pros::v5::MotorGears::rpm_600);
pros::Motor midMotor(8, pros::v5::MotorGears::rpm_200);
pros::Motor outtakeMotor(-3, pros::v5::MotorGears::rpm_200);
pros::Motor sortMotor(-9, pros::v5::MotorGears::rpm_200);

pros::Optical cSensor(1);
pros::Optical cSensor2(5);
pros::Distance dSensor(6);
pros::Distance intakeSensor(21);

pros::ADIDigitalOut matchLoad('G', false);
// pros::ADIDigitalIn matchLoadIn('G');
//pros::ADIDigitalOut wingL('C', false);
// pros::ADIDigitalIn wingLIn('C');
pros::ADIDigitalOut middleDescore('F', false);
// pros::ADIDigitalIn middleDescoreIn('D');
pros::ADIDigitalOut wingR('D', false);
// pros::ADIDigitalIn wingRIn('D');
//pros::ADIDigitalOut intakeLift('I', false);
// pros::ADIDigitalIn intakeLiftIn('E');
pros::ADIDigitalOut feet('B', false);

pros::ADIDigitalOut wingL('B', false);
// pros::ADIDigitalIn feetIn('B');
pros::ADIDigitalOut hood('H', false);
// pros::ADIDigitalIn hoodIn('H');
pros::ADIDigitalOut roof('E', false);
// pros::ADIDigitalIn roofIn('H');

//pros::ADIDigitalOut middleDescore('H', false);

 
//inertial Sensor
pros::Imu inertial(10);
//pros::Distance distLeft(9);
pros::Distance distRight(5);
pros::Distance distFront(7);
pros::Distance distBack(6);

//odometry
pros::Rotation horizontalRotation(-4);
pros::Rotation verticalRotation(-14);

//lemlib::TrackingWheel horizontal_tracking_wheel(&horizontalRotation, lemlib::Omniwheel::NEW_275, 2.65);

//lemlib::TrackingWheel vertical_tracking_wheel(&verticalRotation, lemlib::Omniwheel::NEW_275, 0.625);


lemlib::TrackingWheel horizontal_tracking_wheel(&horizontalRotation, lemlib::Omniwheel::NEW_2,+3);


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
                              10.9, //10.8 inches width
                              lemlib::Omniwheel::NEW_325,
                              450, //drivetrain rpm
                                2 // horizontal drift
);

lemlib::OdomSensors sensors(nullptr, //&vertical_tracking_wheel
                            nullptr,
                            &horizontal_tracking_wheel, // horizontal tracking wheel
                            nullptr,
                            &inertial // inertial sensor
);

lemlib::ControllerSettings lateral_controller(
  6, //kP
  0.0, //kI
  12, //kD
  3.0, // anti windup
  1, // small error range in inches
  30, // small error range timeout, in miliseconds
  3, // large error range in inches
  120, // large error range timeout, in miliseconds
  7 // max acceleration (slew)
);
lemlib::ControllerSettings angular_controller(
  3.3, // proportional gain (kP)
  0, // integral gain (kI)
  22, // derivative gain (kD)
  3, // anti windup
  2, // small error range, in degrees
  30, // small error range timeout, in milliseconds
  5, // large error range, in degrees
  60, // large error range timeout, in milliseconds
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

pros::Task printTask(Autonomous::print);
pros::Task intakeTask(Control::intakeLoop);
pros::Task matchMacroTask(Autonomous::matchMacroExit);
