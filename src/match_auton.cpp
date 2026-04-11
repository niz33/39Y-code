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
    chassis.setPose(0,0,180);
    
    matchLoad.set_value(false);
    Control::intakeState = Control::IntakeState::storage;


    chassis.turnToPoint(10,21,700,{.forwards=false,.maxSpeed=75},false);
    chassis.moveToPoint(10,21,1200,{.forwards=false,.maxSpeed=90,.minSpeed=90,.earlyExitRange=15},false);
    //matchLoad.set_value(true);
    chassis.moveToPoint(10,21,1200,{.forwards=false,.maxSpeed=50},false);
    matchLoad.set_value(false);
    chassis.turnToPoint(2,33,800,{.forwards=false,.maxSpeed=75},false);
    //middleDescore.set_value(true);
    chassis.moveToPoint(1,34,800,{.forwards=false,.maxSpeed=60},false);
    Control::intakeState = Control::IntakeState::lowGoal;
    pros::delay(1000);


    Control::intakeState = Control::IntakeState::storage;
    matchLoad.set_value(true);
    //middleDescore.set_value(false);
    chassis.moveToPoint(31,5,1200,{.forwards=true,.maxSpeed=90,.minSpeed=30,.earlyExitRange=3},false);
    chassis.turnToPoint(32,-20,800,{.forwards=false,.maxSpeed=75},false);
    //intakeMotor.move_voltage(12000);
    //outtakeMotor.move_velocity(-50);
    chassis.moveToPoint(32,-20,1200,{.forwards=false,.maxSpeed=50},true);
    pros::delay(1200);
    chassis.moveToPoint(34,25,1200,{.forwards=true,.maxSpeed=90},true);
    scoreLongMatch(color::red,1000);

    chassis.setPose(0,0,chassis.getPose().theta);
    // descore();

    // matchLoad.set_value(false);
    // chassis.moveToPoint(0, -16, 1200, {.forwards = true,.minSpeed=30,.earlyExitRange=3},false);
    // chassis.moveToPose(8.2, 16, 180, 10000, {.forwards = false,.minSpeed=70},false);
    // rightWheels.move_velocity(0);
    // leftWheels.move_velocity(0);

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
    chassis.moveToPoint(44.5,-25,900,{.forwards=false,.maxSpeed=50},false);

    
    chassis.moveToPoint(46,25,1200,{.forwards=true,.maxSpeed=130},true);
    scoreLongMatch(color::red,1200);

;
    chassis.setPose(0,0,chassis.getPose().theta);

    matchLoad.set_value(false);
    chassis.moveToPoint(-16,6,1000,{.forwards=false,.maxSpeed=60,.minSpeed=30,.earlyExitRange=8},false);


    chassis.moveToPoint(-72,6,1500,{.forwards=false,.maxSpeed=100,.minSpeed=30,.earlyExitRange=30},false);
    chassis.moveToPoint(-72,6,1500,{.forwards=false,.maxSpeed=80,.minSpeed=30,.earlyExitRange=17},false);
    
    chassis.moveToPoint(-72,6,1500,{.forwards=false,.maxSpeed=80,.minSpeed=30,.earlyExitRange=8},false);
    chassis.moveToPoint(-95,-10,1500,{.forwards=false,.maxSpeed=100},false);
    matchLoad.set_value(true);
    chassis.turnToPoint(-97,20,800,{.forwards=true,.maxSpeed=80},false);
    chassis.moveToPoint(-97,20,1000,{.forwards=true,.maxSpeed=100,.minSpeed=80},true);
    scoreLongMatch(color::red,1000);
    
    chassis.setPose(0,0,chassis.getPose().theta);

    Control::intakeState = Control::IntakeState::storage;
    chassis.moveToPoint(1,-45,1000,{.forwards=false,.maxSpeed=60,.minSpeed=30,.earlyExitRange=25},false);
    chassis.moveToPoint(1,-45,700,{.forwards=false,.maxSpeed=50},false);


    chassis.setPose(chassis.getPose().x,0,chassis.getPose().theta);
    chassis.moveToPoint(0,15,500,{.forwards=true,.maxSpeed=100,.minSpeed=30,.earlyExitRange=14},false);
    //chassis.moveToPoint(35,45,1200,{.forwards=true,.maxSpeed=100},false);
    chassis.moveToPoint(43,54,1800,{.forwards=true,.maxSpeed=100},true);
    
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




