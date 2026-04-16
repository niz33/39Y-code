#include "main.h"


void Autonomous::print(){
    while (true) {
        pros::lcd::print(0, "X: %f", chassis.getPose().x);
        pros::lcd::print(1, "Y: %f", chassis.getPose().y);
        pros::lcd::print(2, "Theta: %f", chassis.getPose().theta);
        pros::lcd::print(3, "Intake: %f", Control::IntakeTorque);
        pros::lcd::print(4, "Mid: %f", Control::MidTorque);
        pros::lcd::print(5, "Sort: %f", Control::SortVelocity);
        pros::lcd::print(6, "Outtake: %f", Control::outtakeIntegral);
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

void Autonomous::test(){
    //leftWheels.set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
	//rightWheels.set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
    chassis.setPose(0,0,0);
    //chassis.moveToPoint(0,50,5000,{.forwards=true,.maxSpeed=90},false);
    chassis.turnToPoint(30,0,5000,{.forwards=true,.maxSpeed=75},false);
    chassis.moveToPoint(30,0,5000,{.forwards=true,.maxSpeed=90},false);
    chassis.turnToPoint(0,0,5000,{.forwards=true,.maxSpeed=75},false);
    chassis.moveToPoint(0,0,5000,{.forwards=true,.maxSpeed=90},false);
    chassis.turnToHeading(0,5000,{.maxSpeed=75},false);
    //chassis.turnToHeading(200,5000,{.maxSpeed=75},false);
    //chassis.moveToPose(0,48,0,5000,{},false);
    // chassis.moveToPose(0,0,0,5000,{.forwards=false},false);
}

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

void Autonomous::scoreLongMatch(color c,int scoringTime){
    for(int i=1;i<=140;i++){
        if(distFront.get()<90){
            break;
        }
        pros::delay(10);
    }

    chassis.cancelMotion();
    leftWheels.move_voltage(3000);
    rightWheels.move_voltage(3000);

    Control::intakeState = Control::IntakeState::longGoal;
    pros::delay(scoringTime);
    Control::intakeState = Control::IntakeState::storage;

}

 
void Autonomous::scoreHighMatch(color c,int scoringTime){
    for(int i=1;i<=140;i++){
        if(distFront.get()<180){
            break;
        }
        pros::delay(10);
    }

    chassis.cancelMotion();
    leftWheels.move_voltage(1500);
    rightWheels.move_voltage(1500);

    Control::intakeState = Control::IntakeState::highGoalSlow;
    pros::delay(scoringTime);
    Control::intakeState = Control::IntakeState::storage;

}
void Autonomous::matchDescore(){

    chassis.setPose(0,0,0);
    matchLoad.set_value(false);
    chassis.moveToPoint(-11,1,1200,{.forwards=false,.minSpeed=120,.earlyExitRange=2},false);
    //chassis.moveToPose(-12,1,40,1200,{.forwards=false,.minSpeed=30,.earlyExitRange=7},false);
    chassis.turnToHeading(20,900,{.minSpeed=60,.earlyExitRange=5},false);
    chassis.moveToPoint(-10,10,2000,{.forwards=true, .minSpeed=120,.earlyExitRange=5},false);
    //chassis.moveToPoint(-10.5,2,2000,{.forwards=true, .minSpeed=90},false);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);

 
}

void Autonomous::matchMacroExit(){

    
    while(true){
        int leftY = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int leftX = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        if (leftX > 20 || leftX < -20 || leftY > 20 || leftY < -20) {
            chassis.cancelAllMotions();
        } 
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)){
            Control::wingRState=!Control::wingRState;
            wingR.set_value(Control::wingRState);
	    }
        pros::delay(10);
    }
    
 
}

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