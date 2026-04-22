#include "lemlib/chassis/chassis.hpp"
#include "main.h"

// void Autonomous::matchLeft2Goal(){
//     currentAngle=0;
//     chassis.setPose(0,0,0);
    
//     matchLoad.set_value(false);
//     intakeMotor.move_voltage(12000);
//     outtakeMotor.move_velocity(-50);

//     //turn and move to mid goal
//     //chassis.turnToPoint(-11,22,900,{.forwards=true},false);
//     //chassis.turnToPoint(-11,22,500,{.forwards=true,.maxSpeed=80},false);
//     chassis.moveToPoint(-8,20,1400,{.forwards=true,.maxSpeed=90},false);
//     matchLoad.set_value(true);
//     //chassis.turnToPoint(5,35,1200,{.forwards=false},false);
//     //chassis.turnToPoint(5,35,800,{.forwards=false,.maxSpeed=80},false);
//     chassis.turnToPoint(7,36,800,{.forwards=false,.maxSpeed=80},false);
//     chassis.moveToPoint(7,36,1200,{.forwards=false,.maxSpeed=110},true);

//     //score mid goal
//     intakeMotor.move_velocity(-300);
//     outtakeMotor.move_velocity(-600);
//     pros::delay(300);
//     intakeMotor.move_velocity(600);
//     outtakeMotor.move_velocity(0);
//     pros::delay(1200);

//     //go to matchload
//     intakeMotor.move_velocity(0);
//     outtakeMotor.move_velocity(0);
//     pros::delay(100);
    
//     chassis.moveToPoint(-31,0,1500,{.forwards=true,.maxSpeed=130,.minSpeed=50,.earlyExitRange=10},false);
//     //chassis.turnToPoint(-34,-19,800,{.forwards=true},false);
    
    
//     intakeMotor.move_voltage(12000);
//     outtakeMotor.move_velocity(-50);
//     chassis.turnToHeading(180,700,{.maxSpeed=80},false);
//     chassis.setPose(distLeft.get()*0.0393701*cos(chassis.getPose().theta/180*3.1415926-3.1415926),chassis.getPose().y,chassis.getPose().theta);

//     chassis.moveToPoint(18,-19,700,{.forwards=true,.maxSpeed=60},false);

//     //matchloading
//     //pros::delay(200);
//     chassis.moveToPoint(18,-100,600,{.forwards=true},true);
//     //pros::delay(300);
    
//     //leaving match load
//     //chassis.turnToPoint(-33,25,500,{.forwards=false},false);
//     chassis.moveToPoint(18.5,27,400,{.forwards=false,.maxSpeed=100},false);
//     chassis.moveToPoint(18.5,27,1500,{.forwards=false,.maxSpeed=80},true);
//     scoreLongMatch();

    


//     chassis.setPose(0,0,chassis.getPose().theta);
//     descore();

// }

// void Autonomous::matchLeft1Goal(){
//     currentAngle=0;
//     chassis.setPose(0,0,0);
    
//     matchLoad.set_value(false);
//     intakeMotor.move_voltage(12000);
//     outtakeMotor.move_velocity(-50);

//     //turn and move to mid goal
//     //chassis.turnToPoint(-11,22,900,{.forwards=true},false);
//     //chassis.turnToPoint(-11,22,500,{.forwards=true,.maxSpeed=80},false);
//     chassis.moveToPoint(-8,20,1400,{.forwards=true,.maxSpeed=90},false);
//     matchLoad.set_value(true);
//     //chassis.turnToPoint(5,35,1200,{.forwards=false},false);
//     //chassis.turnToPoint(5,35,800,{.forwards=false,.maxSpeed=80},false);
    
//     chassis.moveToPoint(-31,-5,1500,{.forwards=true,.maxSpeed=130,.minSpeed=50,.earlyExitRange=10},false);
//     //chassis.turnToPoint(-34,-19,800,{.forwards=true},false);
    
    
//     intakeMotor.move_voltage(12000);
//     outtakeMotor.move_velocity(-50);
//     chassis.turnToHeading(180,700,{.maxSpeed=80},false);
//     chassis.setPose(distLeft.get()*0.0393701*cos(chassis.getPose().theta/180*3.1415926-3.1415926),chassis.getPose().y,chassis.getPose().theta);

//     chassis.moveToPoint(18,-19,700,{.forwards=true,.maxSpeed=60},false);

//     //matchloading
//     //pros::delay(200);
//     chassis.moveToPoint(18,-100,600,{.forwards=true},true);
//     //pros::delay(300);
    
//     //leaving match load
//     //chassis.turnToPoint(-33,25,500,{.forwards=false},false);
//     chassis.moveToPoint(18.5,27,400,{.forwards=false,.maxSpeed=100},false);
//     chassis.moveToPoint(18.5,27,1500,{.forwards=false,.maxSpeed=80},true);
//     scoreLongMatch();

    


//     chassis.setPose(0,0,chassis.getPose().theta);
//     descore();


// }



void Autonomous::matchRight2Goal(){
    chassis.setPose(16,0,90);
    
    matchLoad.set_value(false);
    Control::intakeState = Control::IntakeState::storage;

    chassis.moveToPoint(45.5,0,1500,{.forwards=true},false);
    matchLoad.set_value(true);
    chassis.turnToPoint(45.5,-25,1200,{.forwards=false,.maxSpeed=80},false);

    //matchloading
    chassis.moveToPoint(45.5,-25,900,{.forwards=false,.maxSpeed=60, .minSpeed = 60},false);
    chassis.moveToPoint(46.5,25,1200,{.forwards=true,.maxSpeed=130},true);
    scoreLongMatch(color::red,800);
    matchLoad.set_value(false);
    chassis.setPose(0,0,chassis.getPose().theta);
    

    chassis.moveToPoint(-16,6,1000,{.forwards=false,.maxSpeed=60,.minSpeed=30,.earlyExitRange=8},false);
    chassis.moveToPoint(-25,9.5,1500,{.forwards=false,.maxSpeed=100,.minSpeed=30,.earlyExitRange=8},false);
    chassis.moveToPoint(-36,20,1700,{.forwards=false,.maxSpeed=70},false);
    chassis.moveToPoint(-33,17,200,{.forwards=true,.maxSpeed=70},false);
    Control::intakeState = Control::IntakeState::lowGoalSlow;
    pros::delay(400);
    Control::intakeState = Control::IntakeState::lowGoalSlow;
    pros::delay(1000);

    chassis.setPose(0,0,chassis.getPose().theta);
    chassis.moveToPoint(25,-28,1500,{.forwards=true,.maxSpeed=100,.minSpeed=30,.earlyExitRange=4},false);
    chassis.turnToPoint(24,-10,1200,{.forwards=true,.maxSpeed=80,.minSpeed=30,.earlyExitRange=4},false);
    chassis.moveToPoint(24,0,1200,{.forwards=true,.maxSpeed=100},false);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);

}

void Autonomous::matchRightCenter(){
    chassis.setPose(15,0,90);
    
    matchLoad.set_value(false);
    Control::intakeState = Control::IntakeState::storage;

    chassis.moveToPoint(45.5,0,1500,{.forwards=true},false);
    matchLoad.set_value(true);
    chassis.turnToPoint(45.5,-25,1200,{.forwards=false,.maxSpeed=80},false);

    //matchloading
    chassis.moveToPoint(45.5,-25,900,{.forwards=false,.maxSpeed=50},false);
    chassis.setPose(chassis.getPose().x,0,chassis.getPose().theta);
    
    chassis.moveToPoint(chassis.getPose().x,20,1000,{.forwards=true,.maxSpeed=100},false);
    chassis.turnToPoint(15,45,1000,{.forwards=false,.maxSpeed=80},false);
    matchLoad.set_value(false);
    chassis.moveToPoint(15,45,1500,{.forwards=false,.maxSpeed=100,.minSpeed=30,.earlyExitRange=8},false);
    chassis.moveToPoint(10,50,1500,{.forwards=false,.maxSpeed=100},false);
    Control::intakeState = Control::IntakeState::lowGoal;
    pros::delay(800);
    Control::intakeState = Control::IntakeState::storage;
    chassis.moveToPoint(10,40,1000,{.forwards=true,.maxSpeed=100},false);
    Control::intakeState = Control::IntakeState::storage;
    chassis.turnToPoint(-22,40,800,{.forwards=false,.maxSpeed=80},false);
    chassis.moveToPoint(-22,40,1500,{.forwards=false,.maxSpeed=100},false);
    
    chassis.turnToPoint(-9,56,800,{.forwards=true,.maxSpeed=80},false);
    chassis.moveToPoint(-9,56,1500,{.forwards=true,.maxSpeed=100},false);
    Control::intakeState = Control::IntakeState::highGoalSlow;
}
 

void Autonomous::matchLeft2Goal(){
    chassis.setPose(-13,0,-90);
    
    matchLoad.set_value(false);
    Control::intakeState = Control::IntakeState::storage;

    chassis.moveToPoint(-44,0,1500,{.forwards=true},false);
    matchLoad.set_value(true);
    chassis.turnToPoint(-46.5,-25,1200,{.forwards=false,.maxSpeed=80},false);

    //matchloading
    chassis.moveToPoint(-46.5,-25,900,{.forwards=false,.maxSpeed=50},false);
    chassis.moveToPoint(-48,25,1200,{.forwards=true,.maxSpeed=130},true);
    scoreLongMatch(color::red,900);
    matchLoad.set_value(false);
    chassis.setPose(0,0,chassis.getPose().theta);
    

    chassis.moveToPoint(18,1,1000,{.forwards=false,.maxSpeed=90,.minSpeed=30,.earlyExitRange=8},false);
    chassis.moveToPoint(28,2,1500,{.forwards=false,.maxSpeed=100,.minSpeed=30,.earlyExitRange=3},false);
    //chassis.turnToHeading(80,200,{.maxSpeed=80},false);
    chassis.turnToPoint(39,19,1500,{.forwards=true,.maxSpeed=80},false);
    chassis.moveToPoint(39,19,800,{.forwards=true,.maxSpeed=100},false);
    Control::intakeState = Control::IntakeState::highGoalSlow;
    pros::delay(800);
    chassis.setPose(0,0,chassis.getPose().theta);

    chassis.moveToPoint(-26,-28,1200,{.forwards=false,.maxSpeed=100},false);
    chassis.turnToPoint(-28,-10,800,{.forwards=true,.maxSpeed=80},false);
    chassis.moveToPoint(-28,0,1200,{.forwards=true,.maxSpeed=100},false);


}

void Autonomous::matchRight1Goal(){
    chassis.setPose(0,0,196.5);
    
    wingR.set_value(true);
    matchLoad.set_value(false);
    Control::intakeState = Control::IntakeState::storage;

    chassis.moveToPoint(10,24,1500,{.forwards=false,.minSpeed=30,.earlyExitRange=6},false);
    
    chassis.moveToPoint(10,24,1500,{.forwards=false,.minSpeed=30,.earlyExitRange=3},false);
    matchLoad.set_value(true);
    chassis.turnToPoint(31,0,200,{.forwards=false,.maxSpeed=80,.minSpeed=30,.earlyExitRange=5},false);
    chassis.moveToPoint(31,0,1500,{.forwards=false,.minSpeed=30,.earlyExitRange=7},false);
    //matchloading
    chassis.moveToPoint(31,-25,1050,{.forwards=false,.maxSpeed=60},false);
    chassis.moveToPoint(31.5,25,1200,{.forwards=true,.maxSpeed=130},true);
    scoreLongMatch(color::red,900);

    chassis.setPose(0,0,0);
    matchLoad.set_value(false);
    wingR.set_value(false);
    chassis.moveToPoint(-11,1,1200,{.forwards=false,.minSpeed=120,.earlyExitRange=2},false);
    //chassis.moveToPose(-12,1,40,1200,{.forwards=false,.minSpeed=30,.earlyExitRange=7},false);
    chassis.turnToHeading(20,1500,{.minSpeed=60,.earlyExitRange=4},false);
    chassis.moveToPoint(-10,10,2000,{.forwards=true, .minSpeed=120,.earlyExitRange=5},false);
    //chassis.moveToPoint(-10.5,2,2000,{.forwards=true, .minSpeed=90},false);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);

}

void Autonomous::matchRight1Goal8Ball(){
    chassis.setPose(0,0,196.5);
    
    wingR.set_value(true);
    matchLoad.set_value(false);
    Control::intakeState = Control::IntakeState::storage;

    chassis.moveToPoint(10,24,1500,{.forwards=false,.minSpeed=30,.earlyExitRange=6},false);
    
    chassis.moveToPoint(10,24,1500,{.forwards=false,.minSpeed=30,.earlyExitRange=3},false);
    chassis.turnToPoint(25, 39, 1000, {.forwards=false,.maxSpeed=80,.minSpeed=30,.earlyExitRange=3}, false);
    chassis.moveToPoint(25, 39, 1000, {.forwards=false,.maxSpeed=80,.minSpeed=30,.earlyExitRange=3}, false);
    chassis.swingToHeading(280, lemlib::DriveSide::LEFT, 1000,{.maxSpeed=80,.minSpeed=30,.earlyExitRange=3}, false);
    chassis.swingToHeading(225, lemlib::DriveSide::LEFT, 1000,{.maxSpeed=80,.minSpeed=30,.earlyExitRange=3}, false);

    
    
    chassis.moveToPoint(10,24,1500,{.forwards=true,.minSpeed=30,.earlyExitRange=3},false);
    chassis.turnToPoint(31,0,200,{.forwards=false,.maxSpeed=80,.minSpeed=30,.earlyExitRange=5},false);
    matchLoad.set_value(true);

    chassis.moveToPoint(31,0,1500,{.forwards=false,.minSpeed=30,.earlyExitRange=7},false);
    //matchloading
    chassis.moveToPoint(29,-25,1050,{.forwards=false,.maxSpeed=70, .minSpeed = 50},false);
    chassis.moveToPoint(31.5,25,1200,{.forwards=true,.maxSpeed=130},true);
    scoreLongMatch(color::red,900);

    chassis.setPose(0,0,0);
    matchLoad.set_value(false);
    wingR.set_value(false);
    chassis.moveToPoint(-11,1,1200,{.forwards=false,.minSpeed=120,.earlyExitRange=2},false);
    //chassis.moveToPose(-12,1,40,1200,{.forwards=false,.minSpeed=30,.earlyExitRange=7},false);
    chassis.turnToHeading(20,1500,{.minSpeed=60,.earlyExitRange=4},false);
    chassis.moveToPoint(-10,10,2000,{.forwards=true, .minSpeed=120,.earlyExitRange=5},false);
    //chassis.moveToPoint(-10.5,2,2000,{.forwards=true, .minSpeed=90},false);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);

}


void Autonomous::matchLeft1Goal(){
    chassis.setPose(0,0,166);
    
    matchLoad.set_value(false);
    Control::intakeState = Control::IntakeState::storage;

    chassis.moveToPoint(-9,25,1500,{.forwards=false,.minSpeed=30,.earlyExitRange=6},false);
    chassis.moveToPoint(-9,25,1500,{.forwards=false,.minSpeed=30,.earlyExitRange=3},false);
    matchLoad.set_value(true);
    chassis.turnToPoint(-35,0,200,{.forwards=false,.maxSpeed=80,.minSpeed=30,.earlyExitRange=5},false);
    chassis.moveToPoint(-35,0,1500,{.forwards=false,.minSpeed=30,.earlyExitRange=5},false);
    //matchloading
    chassis.moveToPoint(-36,-25,1050,{.forwards=false,.maxSpeed=60},false);
    chassis.moveToPoint(-37.4,25,1200,{.forwards=true,.maxSpeed=130},true);
    scoreLongMatch(color::red,900);

    chassis.setPose(0,0,chassis.getPose().theta);
    matchLoad.set_value(false);
    chassis.moveToPoint(-10.8,1,1200,{.forwards=false,.minSpeed=120,.earlyExitRange=2},false);
    //chassis.moveToPose(-12,1,40,1200,{.forwards=false,.minSpeed=30,.earlyExitRange=7},false);
    chassis.turnToHeading(20,500,{.minSpeed=60,.earlyExitRange=5},false);
    chassis.moveToPoint(-9,20,2000,{.forwards=true, .minSpeed=120,.earlyExitRange=8},false);
    //chassis.moveToPoint(-10.5,2,2000,{.forwards=true, .minSpeed=90},false);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);

}


// void Autonomous::matchRight1Goal(){
//     chassis.setPose(0,0,0);
    
//     matchLoad.set_value(false);
//     intakeMotor.move_voltage(12000);
//     outtakeMotor.move_velocity(0);


//     chassis.turnToPoint(10,21,700,{.forwards=true,.maxSpeed=75},false);
//     chassis.moveToPoint(10,21,1200,{.forwards=true,.maxSpeed=90,.minSpeed=90,.earlyExitRange=10},false);
//     matchLoad.set_value(true);
//     chassis.moveToPoint(10,21,1200,{.forwards=true,.maxSpeed=50},false);
    

//     chassis.moveToPoint(34,0,1400,{.forwards=false,.maxSpeed=90,.minSpeed=30,.earlyExitRange=3},false);
//     chassis.turnToPoint(34,-20,1500,{.forwards=true,.maxSpeed=75},false);
//     intakeMotor.move_voltage(12000);
//     outtakeMotor.move_velocity(-50);
//     chassis.moveToPoint(33,-25,1200,{.forwards=true,.maxSpeed=50},true);
//     pros::delay(900);
//     chassis.moveToPoint(35,20,1200,{.forwards=false,.maxSpeed=90},true);
//     scoreLongMatch(color::red);

//     chassis.setPose(0,0,chassis.getPose().theta);
//     descore();
// }


void Autonomous::matchSolo(){
    chassis.setPose(0,0,90);
    Control::intakeState = Control::IntakeState::storage;
    double originalTime = pros::millis();
    matchLoad.set_value(false);

    //intakeMotor.move_voltage(12000);
    //outtakeMotor.move_velocity(-50);

    chassis.moveToPoint(-7,0,500,{.forwards=false},false);
    chassis.moveToPoint(44.5,0,1500,{.forwards=true},false);
    matchLoad.set_value(true);
    chassis.turnToPoint(44.5,-25,1200,{.forwards=false,.maxSpeed=80},false);
    

    //matchloading
    chassis.moveToPoint(44.5,-25,800,{.forwards=false,.maxSpeed=70, .minSpeed = 50},false);

    
    chassis.moveToPoint(46,25,1200,{.forwards=true,.maxSpeed=130},true);
    scoreLongMatch(color::red,1100);


    chassis.setPose(0,0,chassis.getPose().theta);
 
    matchLoad.set_value(false);
    chassis.moveToPoint(-15,9,1500,{.forwards=false,.maxSpeed=60,.minSpeed=30,.earlyExitRange=4},false);

    chassis.moveToPoint(-72,8,1500,{.forwards=false,.maxSpeed=100,.minSpeed=30,.earlyExitRange=30},false);
    chassis.moveToPoint(-72,8,1500,{.forwards=false,.maxSpeed=80,.minSpeed=30,.earlyExitRange=17},false);
    
    chassis.moveToPoint(-72,8,1500,{.forwards=false,.maxSpeed=80,.minSpeed=30,.earlyExitRange=8},false);
    chassis.moveToPoint(-97.5,-10,1500,{.forwards=false,.maxSpeed=100},false);
    matchLoad.set_value(true);
    chassis.turnToPoint(-97.5,20,800,{.forwards=true,.maxSpeed=80},false);
    chassis.moveToPoint(-97.5,20,1000,{.forwards=true,.maxSpeed=100,.minSpeed=80},true);
    scoreLongMatch(color::red,800);
    
    chassis.setPose(0,0,chassis.getPose().theta);

    Control::intakeState = Control::IntakeState::storage;
    chassis.moveToPoint(1,-45,1000,{.forwards=false,.maxSpeed=70,.minSpeed=50,.earlyExitRange=25},false);
    chassis.moveToPoint(1,-45,700,{.forwards=false,.maxSpeed=50},false);


    chassis.setPose(chassis.getPose().x,0,chassis.getPose().theta);
    chassis.moveToPoint(0,15,500,{.forwards=true,.maxSpeed=100,.minSpeed=30,.earlyExitRange=14},false);
    //chassis.moveToPoint(35,45,1200,{.forwards=true,.maxSpeed=100},false);
    chassis.moveToPoint(44.5,54,1800,{.forwards=true,.maxSpeed=85,.minSpeed = 60},true);
    
    scoreHighMatch(color::red,12000);

    // chassis.setPose(0,0,chassis.getPose().theta);
    // chassis.moveToPoint(-28,-28,1200,{.forwards=false,.maxSpeed=100},false);
    // chassis.turnToPoint(-30,-10,800,{.forwards=true,.maxSpeed=80},false);
    // chassis.moveToPoint(-30,-10,1200,{.forwards=true,.maxSpeed=100},false);
    

}




// // void matchLoad(){
// //     for(int i=1;i<=140;i++){
// //         if(rightWheel1.get_actual_velocity()<5){
// //             break;
// //         }
// //         pros::delay(10);
// //     }

// //     rightWheels.move_voltage(2000);
// //     leftWheels.move_voltage(2000);
// //     pros::delay(1700);
// // }




