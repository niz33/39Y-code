#include "main.h"


void Autonomous::print(){
    while (true) {
        pros::lcd::print(0, "X: %f", chassis.getPose().x);
        pros::lcd::print(1, "Y: %f", chassis.getPose().y);
        pros::lcd::print(2, "Theta: %f", chassis.getPose().theta);
        pros::lcd::print(3, "Intake: %f", Control::IntakeTorque);
        pros::lcd::print(4, "Mid: %f", Control::MidTorque);
        pros::lcd::print(5, "Sort: %f", Control::SortTorque);
        pros::lcd::print(6, "Outtake: %f", Control::OuttakeTorque);
        pros::lcd::print(7, "Color: %f", cSensor.get_hue());

        pros::delay(50);
    }
} 

// void Autonomous::intake(){
//     if(intaking){
//         intakeMotor.move_voltage(12000);
//         outtakeMotor.move_velocity(-50);
//         jamFlag*=0.6;
//         //jamFlag+=intakeMotor.get
//     }
// }

// void Autonomous::test(){
//     leftWheels.set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
// 	rightWheels.set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
//     chassis.setPose(0,0,0);
//     chassis.turnToPoint(-30,0,5000,{.forwards=false,.maxSpeed=75},false);
//     chassis.moveToPoint(-30,0,5000,{.forwards=false,.maxSpeed=90},false);
//     chassis.turnToPoint(0,0,5000,{.forwards=false,.maxSpeed=75},false);
//     chassis.moveToPoint(0,0,5000,{.forwards=false,.maxSpeed=90},false);
//     chassis.turnToHeading(0,5000,{.maxSpeed=75},false);
//     // chassis.moveToPose(0,48,0,5000,{},false);
//     // chassis.moveToPose(0,0,0,5000,{.forwards=false},false);
// }

// void Autonomous::distTest(){
//     chassis.setPose(0,0,0, false);

//     double oDist=distLeft.get()*0.0393701*cos(chassis.getPose().theta/180*3.1415926);

//     //pros::lcd::initialize();
//     while (true) {
//         // print robot location to the brain screen
//         pros::lcd::clear();
//         pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
//         pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
//         pros::lcd::print(2, "Y: %f", distLeft.get()*0.0393701*cos(chassis.getPose().theta/180*3.1415926)-oDist);
//         pros::lcd::print(3, "Theta: %f", chassis.getPose().theta); // heading
//         // delay to save resources
//         pros::delay(10);
//     }

// }

// void scoreLong(){
//     for(int i=1;i<=140;i++){
//         if(distStand.get()<100){
//             break;
//         }
//         pros::delay(10);
//     }

//     for(int i=1;i<=210;i++){
//         intakeMotor.move_voltage(12000);
//         outtakeMotor.move_voltage(12000);
//         pros::delay(10);
//     }

//     intakeMotor.move_velocity(0);
//     outtakeMotor.move_velocity(0);
// }

// void scoreLongMatch(color c=color::none,int scoringTime=1900){
//     for(int i=1;i<=140;i++){
//         if(distStand.get()<130){
//             break;
//         }
//         pros::delay(10);
//     }

//     chassis.cancelMotion();
//     leftWheels.move_voltage(-3000);
//     rightWheels.move_voltage(-3000);


//     originalTime = pros::millis();

//     int cDelay=3;
//     std::queue<int> cRight;
//     int flag=0;
//     while(true){
//         int temp=1;

//         if(c==color::red){
//             if (cSensor.get_hue()>80) temp=0;
//         }
//         else if(c==color::blue){
//             if (cSensor.get_hue()<20) temp=0;
//         }

//         cRight.push(temp);
//         if(cRight.front()==0){
//             flag=1;
//         }
//         if(cRight.size()>=cDelay){
//             cRight.pop();
//         }
//         if(flag==1){
//             intakeMotor.move_voltage(12000);
//             outtakeMotor.move_velocity(-50);
//             // intakeMotor.move_voltage(12000);
//             // outtakeMotor.move_voltage(12000);
//         }
//         if(flag==0){
//             intakeMotor.move_voltage(12000);
//             outtakeMotor.move_voltage(12000);
//         }
//         //back out at the end
//         if (pros::millis() >= scoringTime + originalTime){//11800
//             // drivetrain.leftMotors->move_voltage(-12000);
//             // drivetrain.rightMotors->move_voltage(-12000);
//             break;
//         }
//         pros::delay(5);
//     }


// }

// void descore(){

//     matchLoad.set_value(false);
//     chassis.moveToPoint(0,-15,1200,{.forwards=true,.minSpeed=30,.earlyExitRange=3},false);
//     chassis.moveToPose(7,15,180,2000,{.forwards=false, .minSpeed=60,.earlyExitRange=10},false);
//     chassis.moveToPose(9,17,180,2000,{.forwards=false, .minSpeed=90},false);
//     chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);

 

    
// }

// void scoreSeven(){
//     intakeMotor.move_velocity(300);
//     outtakeMotor.move_velocity(-50);
//     for(int i=1;i<=120;i++){
//         if(cSensor2.get_hue()<30){
//             pros::delay(50);
//             break;
//         }
//         pros::delay(10);
//     }
//     intakeMotor.move_velocity(0);
//     outtakeMotor.move_velocity(0);
// }

// void matchload(){
//     for(int i=1;i<=140;i++){
//         if(distFront.get()<300){
//             break;
//             chassis.cancelMotion();
//         }
//         pros::delay(10);
//     }

//     rightWheels.move_voltage(-6000);
//     leftWheels.move_voltage(-6000);
//     pros::delay(1800);
// }