#include "main.h"

// const double Autonomous::CLOCKWISE_CORRECTION = 360.0 / 357.0;  // Corrects for clockwise turns
// const double Autonomous::COUNTERCLOCKWISE_CORRECTION = 357.0 / 360.0; // Corrects for counterclockwise turns

// double Autonomous::previous_heading = 0.0;
// double Autonomous::corrected_heading = 0.0;



// // class DrivetrainGood : public lemlib::Drivetrain{
// //     DrivetrainGood(lemlib::Drivetrain drivetrain) : lemlib::Drivetrain(drivetrain){}
    
// // };

double currentAngle=0;

void move(int dist, int time){
    chassis.setPose(0,0,0);
    if(dist>0) chassis.moveToPoint(0,dist,time,{},false);
    else chassis.moveToPoint(0,dist,time,{.forwards=false},false);
    currentAngle-=chassis.getPose().theta;
}

void turn(int angle, int time){
    chassis.setPose(0,0,currentAngle);
    chassis.turnToHeading(currentAngle-angle,time,{},false);
    currentAngle-=chassis.getPose().theta;
}

void Autonomous::print(){
    while (true) {
        // print robot location to the brain screen
        pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
        pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
        pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
        // delay to save resources
        pros::delay(100);
    }
}


void Autonomous::test(){
    leftWheels.set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
	rightWheels.set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
    chassis.setPose(0,0,0);
    chassis.turnToPoint(-30,0,5000,{.forwards=false,.maxSpeed=75},false);
    chassis.moveToPoint(-30,0,5000,{.forwards=false,.maxSpeed=90},false);
    chassis.turnToPoint(0,0,5000,{.forwards=false,.maxSpeed=75},false);
    chassis.moveToPoint(0,0,5000,{.forwards=false,.maxSpeed=90},false);
    chassis.turnToHeading(0,5000,{.maxSpeed=75},false);
    // chassis.moveToPose(0,48,0,5000,{},false);
    // chassis.moveToPose(0,0,0,5000,{.forwards=false},false);
}

double originalTime;

void Autonomous::matchForward(){
    leftWheels.move_velocity(100);
    rightWheels.move_velocity(100);
    pros::delay(400);
    leftWheels.move_velocity(0);
    rightWheels.move_velocity(0);
}

void Autonomous::skillsMove() {
    leftWheels.move_voltage(12000);
    rightWheels.move_voltage(12000);
    intakeMotor.move_voltage(12000);
    pros::delay(400);
    leftWheels.move_voltage(0);
    rightWheels.move_voltage(0);
}

void Autonomous::RightMidLong(){
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.setPose(-53.5, -9, 115, false);
    //intake
    intakeMotor.move_voltage(12000);
    chassis.moveToPoint(-24, -23, 2000, {.forwards = true, .maxSpeed = 60},false);
    chassis.turnToHeading(225, 800, {}, false);

    chassis.moveToPoint(-47, -45, 3000, {.forwards = true, .maxSpeed = 60},false);
    
    matchLoad.set_value(true);
    chassis.turnToHeading(270, 2400, {}, false);
    chassis.moveToPoint(-65, -45, 500, {.forwards = true, .maxSpeed = 50},false);
    chassis.moveToPoint(-70, -45, 500, {.forwards = true, .maxSpeed = 50},true);

    pros::delay(980);
    //head to long goal
    //matchLoad.set_value(false);
    chassis.moveToPoint(-25, -45, 1200, {.forwards = false, .maxSpeed = 60},false);
    outtakeMotor.move_voltage(12000);

    int cDelay=10;
    std::queue<int> cRight;
    int flag=0;
    while(true){
        int temp=1;
        //score red
        //if (cSensor.get_hue()>60) temp=0;
        //score blue
        if (cSensor.get_hue()<30) temp=0;
        cRight.push(temp);
        if(cRight.front()==0){
            flag=1;
        }
        if(cRight.size()>=cDelay){
            cRight.pop();
        }
        if(flag==1){
            intakeMotor.move_voltage(12000);
            outtakeMotor.move_velocity(-50);
            // intakeMotor.move_voltage(12000);
            // outtakeMotor.move_voltage(12000);
        }
        if(flag==0){
            intakeMotor.move_voltage(12000);
            outtakeMotor.move_voltage(12000);
        }
        //back out at the end
        if (pros::millis() >= 12000 + originalTime){//11800
            // drivetrain.leftMotors->move_voltage(-12000);
            // drivetrain.rightMotors->move_voltage(-12000);
            break;
        }
        pros::delay(5);
    }
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_velocity(-50);
    
    chassis.setPose(0,0,chassis.getPose().theta);
    chassis.moveToPoint(-15, 0, 1200, {.forwards = true},false);
    chassis.moveToPose(19, -8.75, 270, 10000, {.forwards = false},false);

    while(true){
        if (pros::millis() >= 14800 + originalTime){//11800
            chassis.turnToHeading(240, 1000, {}, false);
            //chassis.moveToPoint(10, -8.75, 1200, {.forwards = true},false);
        }
        pros::delay(5);
    }
}

void Autonomous::matchLeftAutonBlue(){
    currentAngle=0;
    chassis.setPose(0,0,0);
    originalTime = pros::millis();
    matchLoad.set_value(false);
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_velocity(-50);

    //turn and move to mid goal
    chassis.turnToPoint(-11,22,900,{.forwards=true},false);
    chassis.moveToPoint(-11,22,1400,{.forwards=true,.maxSpeed=60},false);
    matchLoad.set_value(true);
    chassis.turnToPoint(3,32,1200,{.forwards=false},false);
    chassis.moveToPoint(3,32,1200,{.forwards=false},false);

    //score mid goal
    intakeMotor.move_velocity(-600);
    outtakeMotor.move_velocity(-600);
    pros::delay(200);
    intakeMotor.move_velocity(600);
    outtakeMotor.move_velocity(300);
    pros::delay(900);

    //go to matchload
    intakeMotor.move_velocity(0);
    outtakeMotor.move_velocity(0);
    pros::delay(100);
    
    chassis.moveToPoint(-35,0,1500,{.forwards=true,.maxSpeed=80},false);
    chassis.turnToPoint(-35,-19,800,{.forwards=true},false);
    
    
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_velocity(-50);
    chassis.moveToPoint(-35
        ,-19,700,{.forwards=true,.maxSpeed=60},false);

    //matchloading
    pros::delay(200);
    chassis.moveToPoint(-36,-100,900,{.forwards=true},true);
    //pros::delay(300);
    
    //leaving match load
    chassis.turnToPoint(-36,25,500,{.forwards=false},false);
    chassis.moveToPoint(-36,27,1500,{.forwards=false},false);

    //scoring long goal
    outtakeMotor.move_voltage(12000);
    chassis.moveToPoint(-36,30,700,{.forwards=false},false);

    int cDelay=3;
    std::queue<int> cRight;
    int flag=0;
    while(true){
        int temp=1;
        //score red
        if (cSensor.get_hue()>80) temp=0;
        //score blue
        //if (cSensor.get_hue()<20) temp=0;
        cRight.push(temp);
        if(cRight.front()==0){
            flag=1;
        }
        if(cRight.size()>=cDelay){
            cRight.pop();
        }
        if(flag==1){
            intakeMotor.move_voltage(12000);
            outtakeMotor.move_velocity(-50);
            // intakeMotor.move_voltage(12000);
            // outtakeMotor.move_voltage(12000);
        }
        if(flag==0){
            intakeMotor.move_voltage(12000);
            outtakeMotor.move_voltage(12000);
        }
        //back out at the end
        if (pros::millis() >= 11800 + originalTime){//11800
            // drivetrain.leftMotors->move_voltage(-12000);
            // drivetrain.rightMotors->move_voltage(-12000);
            break;
        }
        pros::delay(5);
    }
    chassis.setPose(0,0,180);


    chassis.moveToPoint(0,-15,1200,{.forwards=true},false);
    chassis.moveToPose(8.75,17,180,12000,{.forwards=false, .minSpeed=50},false);

    while(true){
        if (pros::millis() >= 14800 + originalTime){//11800
            chassis.turnToHeading(150, 1000, {}, false);
            //chassis.moveToPoint(8.75, 15, 1200, {.forwards = true},false);
        }
        pros::delay(5);
    }
}



void Autonomous::matchLeftAuton2(){
    // originalTime = pros::millis();
    // chassis.setPose(0,0,167);
    // intakeMotor.move_voltage(-3000);
    //     rampMotor.move_voltage(12000);
    //     midMotor.move_voltage(-3000);
    
    // chassis.moveToPose(-8,26,167 ,1500,{.forwards=false},false);
    
    // chassis.moveToPose(16,50,45,1500,{},false);
    // intakeMotor.move_voltage(-10000);
    //     rampMotor.move_voltage(-12000);
    //     midMotor.move_voltage(0);
    //     pros::delay(300);
    // midMotor.move_voltage(10000);
    // intakeMotor.move_voltage(10000); 
    // rampMotor.move_voltage(12000);

    // pros::delay(2100);
    // midMotor.move_voltage(-2000);
    // intakeMotor.move_voltage(-2000);
    // rampMotor.move_voltage(0);
    // pros::delay(500);
    // pneumatic.set_value(true);
    

    // rampMotor.move_voltage(12000);
    // midMotor.move_voltage(-3000);
    // chassis.moveToPoint(-29,0,1200,{.forwards=false},false);
    
    // // chassis.moveToPose(-35,-25,0,750,{.forwards=false},false);
    // chassis.turnToHeading(0,750,{},false);
    // intakeMotor.move_voltage(-3000);
    // drivetrain.leftMotors->move_voltage(-60000);
    // drivetrain.rightMotors->move_voltage(-60000);
    // pros::delay(300);
    // drivetrain.leftMotors->move_voltage(-4000);
    // drivetrain.rightMotors->move_voltage(-4000);
    // pros::delay(1400);

    // chassis.moveToPose(-35.5,50,0,1300,{},false); 
    // drivetrain.leftMotors->move_voltage(5000);
    // drivetrain.rightMotors->move_voltage(5000);
    
    // pros::delay(200);
    // chassis.setPose(0,0,0);
    // midMotor.move_voltage(5000); 
    // intakeMotor.move_voltage(-5000);
    // chassis.moveToPose(0,-1.5,0,300,{},true);
    // rampMotor.move_voltage(12000);
    // midMotor.move_voltage(-10000);
    // intakeMotor.move_voltage(10000);

    // int cDelay=10;
    // std::queue<int> cRight;
    // int countdown=0;
    // while(true){
    //     int temp=1;
    //     if (cSensor.get_hue()>115) temp=0;
    //     cRight.push(temp);
    //     if(cRight.size()>=cDelay&&cRight.front()==0){
    //         countdown=13;
    //     }
    //     if(countdown>0) countdown--;
    //     if(countdown>0){
    //         midMotor.move_voltage(10000);
    //         intakeMotor.move_voltage(2000);
    //         // midMotor.move_voltage(-10000);
    //         // intakeMotor.move_voltage(10000);
    //     }
    //     else{
    //         midMotor.move_voltage(-10000);
    //         intakeMotor.move_voltage(10000);
    //     }
    //     if(cRight.size()>=cDelay){
    //         cRight.pop();
    //     }
    //     if (pros::millis() >= 14800 + originalTime){
    //         drivetrain.leftMotors->move_voltage(-12000);
    //         drivetrain.rightMotors->move_voltage(-12000);
    //     }
    //     pros::delay(10);
        
    // }

    
    
    // // chassis.turnToHeading(-90,750,{},false);
    // // move(22,1250);
    // // pneumatic.set_value(false);

    // // pros::delay(1500);
    // // move(-10,750);
    // // turn(-45,1000);
    // // move(40,1250);
    // // intakeMotor.move_voltage(10000);
    // //     rampMotor.move_voltage(12000);
    // //     midMotor.move_voltage(-10000);
}
void Autonomous::matchLeftAuton3(){

    // rampMotor.move_voltage(12000);

    // int cDelay=1;
    // std::queue<int> cRight;
    // int countdown=0;
    // while(true){
    //     int temp=1;
    //     if (cSensor.get_hue()<35) temp=0;
    //     cRight.push(temp);
    //     if(cRight.size()>=cDelay&&cRight.front()==0){
    //         countdown=13;
    //     }
    //     if(countdown>0) countdown--;
    //     if(countdown>0){
    //         midMotor.move_voltage(10000);
    //         intakeMotor.move_voltage(2000);
    //         // midMotor.move_voltage(-10000);
    //         // intakeMotor.move_voltage(10000);
    //     }
    //     else{
    //         midMotor.move_voltage(-10000);
    //         intakeMotor.move_voltage(10000);
    //     }
    //     if(cRight.size()>=cDelay){
    //         cRight.pop();
    //     }
    //     pros::delay(10);
    // }

}
void Autonomous::matchRightAuton2(){
    chassis.setPose(0,0,0);
    
    matchLoad.set_value(false);
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_velocity(0);


    chassis.turnToPoint(10,21,700,{.forwards=true,.maxSpeed=75},false);
    chassis.moveToPoint(10,21,1200,{.forwards=true,.maxSpeed=90,.minSpeed=60,.earlyExitRange=8},false);
    matchLoad.set_value(true);
    chassis.moveToPoint(10,21,1200,{.forwards=true,.maxSpeed=70},false);
    chassis.turnToPoint(-4,31,800,{.forwards=true,.maxSpeed=75},false);
    matchLoad.set_value(false);
    middleDescore.set_value(true);
    chassis.moveToPoint(-4,31,1200,{.forwards=true,.maxSpeed=90},false);
    intakeMotor.move_velocity(-400);
    pros::delay(900);


    intakeMotor.move_velocity(0);
    matchLoad.set_value(true);
    middleDescore.set_value(false);
    chassis.moveToPoint(33,3,1200,{.forwards=false,.maxSpeed=90},false);
    chassis.turnToPoint(33,-20,1500,{.forwards=true,.maxSpeed=75},false);
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_velocity(-50);
    chassis.moveToPoint(33,-25,1200,{.forwards=true,.maxSpeed=45},true);
    pros::delay(1200);
    chassis.moveToPoint(33,20,1200,{.forwards=false,.maxSpeed=90},true);
    pros::delay(900);

    int cDelay=10;
    originalTime = pros::millis();
    std::queue<int> cRight;
    int flag=0;
    while(true){
        int temp=1;
        //score red
        //if (cSensor.get_hue()>60) temp=0;
        //score blue
        if (cSensor.get_hue()<25) temp=0;
        cRight.push(temp);
        if(cRight.front()==0){
            flag=1;
        }
        if(cRight.size()>=cDelay){
            cRight.pop();
        }
        if(flag==1){
            intakeMotor.move_voltage(12000);
            outtakeMotor.move_velocity(-50);
            break;
        }
        if(flag==0){
            intakeMotor.move_voltage(12000);
            outtakeMotor.move_voltage(12000);
        }
        //back out at the end
        if (pros::millis() >= 1300 + originalTime){//11800
            break;
        }
        pros::delay(5);
    }

    chassis.setPose(0,0,chassis.getPose().theta);
    chassis.moveToPoint(0, -15, 1200, {.forwards = true},false);
    chassis.moveToPose(8.8, 19, 180, 10000, {.forwards = false,.minSpeed=70},false);


}



void Autonomous::skillsAuton(){
    currentAngle=0;
    chassis.setPose(0,0,90);
    originalTime = pros::millis();
    matchLoad.set_value(false);

    chassis.moveToPoint(28,0,1500,{.forwards=true},false);
    matchLoad.set_value(true);
    chassis.turnToHeading(180,1000,{},false);
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_velocity(-50);
    
    chassis.moveToPoint(30,-20,1000,{.forwards=true,.maxSpeed=45},false);

    //matchloading
    pros::delay(200);
    chassis.moveToPoint(30,-25,2500,{.forwards=true,.maxSpeed=30},false);
    //pros::delay(2000);

    chassis.moveToPoint(30,22,1200,{.forwards=false},false);

    //scoring long goal
    outtakeMotor.move_voltage(12000);
    chassis.moveToPoint(30,27,500,{.forwards=false},true);
    pros::delay(3000);
    chassis.setPose(0,0,chassis.getPose().theta);
    matchLoad.set_value(false);

    //middle
    intakeMotor.move_velocity(0);
    outtakeMotor.move_velocity(0);
    chassis.moveToPoint(0,-11,1200,{.forwards=true},false);
    chassis.turnToPoint(-18,1,800,{.forwards=true},false);
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_velocity(-50);
    chassis.moveToPoint(-18,1,1000,{.forwards=true,.maxSpeed=60},false);
    //matchLoad.set_value(true);

    chassis.turnToPoint(-68,0,800,{.forwards=true},false);
    matchLoad.set_value(false);
    chassis.moveToPoint(-70,0,1500,{.forwards=true,.maxSpeed=60},false);
    matchLoad.set_value(true);

    
    chassis.turnToPoint(-92,-15,1200,{.forwards=true},false);
    intakeMotor.move_voltage(0);
    chassis.moveToPoint(-92,-15,1200,{.forwards=true},false);

    chassis.turnToPoint(-92,5,800,{.forwards=false},false);
    chassis.moveToPoint(-92,5,800,{.forwards=false},false);

    //scoring high goal
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_voltage(12000);
    chassis.moveToPoint(-92,12,500,{.forwards=false},true);
    pros::delay(3000);

    chassis.setPose(0,0,chassis.getPose().theta);
    outtakeMotor.move_velocity(0);

    //matchload

    matchLoad.set_value(true);
    chassis.moveToPoint(1.5,-30,1200,{.forwards=true,.maxSpeed=70},false);
    pros::delay(200);
    chassis.moveToPoint(1.5,-35,2200,{.forwards=true,.maxSpeed=30},false);
    chassis.moveToPoint(1.5,-39,300,{.forwards=true,.maxSpeed=70},false);
    //pros::delay(2000);

    //score long

    chassis.moveToPoint(0,10,1500,{.forwards=false,.maxSpeed=70},false);
    pros::delay(1000);
    outtakeMotor.move_voltage(12000);
    chassis.moveToPoint(0,20,1000,{.forwards=false},true);
    
    pros::delay(3000);
    chassis.setPose(0,0,chassis.getPose().theta);
    //park
    matchLoad.set_value(false);
    outtakeMotor.move_velocity(0);
    chassis.moveToPose(25,-15,90,1200,{.forwards=true},false);
    chassis.moveToPose(32,-33,90,3000,{.forwards=true},false);
    //matchLoad.set_value(true);
    chassis.moveToPoint(8,-34,500,{.forwards=false},false);
    leftWheels.move_velocity(500);
    rightWheels.move_velocity(500);
    pros::delay(1350);
    leftWheels.move_velocity(0);
    rightWheels.move_velocity(0);
    //dfdchassis.moveToPoint(57,-34,3000,{.forwards=true},false);
    //matchLoad.set_value(false);

}










void scoreHigh(){
    for(int i=1;i<=140;i++){
        if(distStand.get()<100){
            break;
        }
        pros::delay(10);
    }

    for(int i=1;i<=210;i++){
        intakeMotor.move_voltage(12000);
        outtakeMotor.move_voltage(12000);
        pros::delay(10);
    }

    intakeMotor.move_velocity(0);
    outtakeMotor.move_velocity(0);
}

// void matchLoad(){
//     for(int i=1;i<=140;i++){
//         if(rightWheel1.get_actual_velocity()<5){
//             break;
//         }
//         pros::delay(10);
//     }

//     rightWheels.move_voltage(2000);
//     leftWheels.move_voltage(2000);
//     pros::delay(1700);
// }

void scoreSeven(){
    intakeMotor.move_velocity(300);
    outtakeMotor.move_velocity(-50);
    for(int i=1;i<=120;i++){
        if(cSensor.get_hue()<30){
            pros::delay(50);
            break;
        }
        pros::delay(10);
    }
    intakeMotor.move_velocity(0);
    outtakeMotor.move_velocity(0);
}


void Autonomous::skillsAuton2(){

    int matchLoadTime=2000;
    currentAngle=0;
    chassis.setPose(0,0,-90);
    originalTime = pros::millis();
    matchLoad.set_value(false);

    //intake parking
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_velocity(-50);
    chassis.moveToPoint(-60,0,800,{.forwards=true,.maxSpeed=80},false);
    chassis.moveToPoint(-60,0,1500,{.forwards=true,.maxSpeed=80},false);
    
    //calibration
    chassis.turnToHeading(180,1000,{.maxSpeed=75},false);

    chassis.moveToPoint(-56,-100000,500,{.forwards=true,.maxSpeed=50},false);
    intakeMotor.move_voltage(0);
    chassis.setPose(chassis.getPose().x,7.5,chassis.getPose().theta);
    chassis.moveToPoint(chassis.getPose().x,30,1200,{.forwards=false,.maxSpeed=90},false);
    //pros::delay(300);
    chassis.setPose(distLeft.get()*0.0393701*cos(chassis.getPose().theta/180*3.1415926-3.1415926)+5,chassis.getPose().y,chassis.getPose().theta);

    //chassis.moveToPose(42,42,45,2000,{.forwards=true,.maxSpeed=90},false);
    
    //score high goal
    chassis.turnToPoint(56,56,1000,{.forwards=false,.maxSpeed=75},false);
    matchLoad.set_value(true);
    chassis.moveToPoint(56,56,1200,{.forwards=false,.maxSpeed=90},false);
    chassis.turnToPoint(64,64,600,{.forwards=false,.maxSpeed=75},false);
    pros::delay(200);
    intakeMotor.move_velocity(-150);
    outtakeMotor.move_velocity(-600);
    chassis.moveToPoint(65,65,500,{.forwards=false,.maxSpeed=90},false);
    intakeMotor.move_velocity(500);
    outtakeMotor.move_velocity(-50);
    pros::delay(700);
    intakeMotor.move_velocity(-100);
    outtakeMotor.move_velocity(-600);
    pros::delay(200);
    intakeMotor.move_velocity(500);
    outtakeMotor.move_velocity(-50);
    pros::delay(1200);
    
    //match load
    chassis.moveToPoint(25,28,1700,{.forwards=true,.maxSpeed=90},false);
    
    chassis.turnToPoint(25,5,1000,{.forwards=true,.maxSpeed=75},false);
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_velocity(-50);
    //chassis.moveToPoint(24,-50,500,{.forwards=true,.maxSpeed=100},false);

    chassis.moveToPoint(25 ,-50,matchLoadTime,{.forwards=true,.maxSpeed=50},false);
    //pros::delay(matchLoadTime);
    chassis.setPose(chassis.getPose().x,14,chassis.getPose().theta);

    

    //go score long goal
    chassis.moveToPose(16,44,180,2000,{.forwards=false,.maxSpeed=110,.minSpeed=50,.earlyExitRange=5},true);
    pros::delay(300);
    matchLoad.set_value(false);
    //intakeMotor.move_velocity(0); 
    //outtakeMotor.move_velocity(0);
    chassis.moveToPoint(17,100,1500,{.forwards=false,.maxSpeed=110,.minSpeed=60,.earlyExitRange=5},false);
    chassis.setPose(distLeft.get()*0.0393701*cos(chassis.getPose().theta/180*3.1415926-3.1415926),chassis.getPose().y,chassis.getPose().theta);
    chassis.moveToPose(23,110,-90,1500,{.forwards=false,.maxSpeed=110},false);
    chassis.turnToPoint(19,80,1000,{.forwards=false,.maxSpeed=75},false);
    chassis.moveToPoint(19,80,1500,{.forwards=false,.maxSpeed=110},true);

    //chassis.moveToPose(28,50,0,1500,{.forwards=false,.maxSpeed=60},true);
    scoreHigh();

    chassis.setPose(0,0,chassis.getPose().theta);

    //long goal second time
    matchLoad.set_value(true);
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_velocity(-50);
    chassis.moveToPoint(0,50,500,{.forwards=true,.maxSpeed=100},false);
    chassis.moveToPoint(0,50,matchLoadTime,{.forwards=true,.maxSpeed=50},false);
    //pros::delay(matchLoadTime);
    
    chassis.moveToPoint(0,-5,1200,{.forwards=false,.maxSpeed=70},true);
    pros::delay(300);
    //intakeMotor.move_voltage(0);
    //outtakeMotor.move_velocity(0);
    scoreHigh();
    matchLoad.set_value(false);
    chassis.setPose(0,0,chassis.getPose().theta);
    
    //second park zone
    //chassis.moveToPoint(18,36,500,{.forwards=true,.maxSpeed=90},false);
    chassis.moveToPoint(18,36,1500,{.forwards=true,.maxSpeed=90},false);
    //chassis.moveToPoint(25,36,1500,{.forwards=true,.maxSpeed=90},false);
    chassis.turnToHeading(70,1000,{.maxSpeed=75},false);
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_velocity(-50);
    
    chassis.moveToPose(45,42,85,500,{.forwards=true,.maxSpeed=90},false);
    pros::delay(400);
    //matchLoad.set_value(true);
    
    chassis.moveToPoint(105,42,3500,{.forwards=true,.maxSpeed=80},false);
    pros::delay(500); 
    intakeMotor.move_velocity(0);
    outtakeMotor.move_velocity(0);
    
    //matchLoad.set_value(false);

    chassis.turnToHeading(0,1000,{.maxSpeed=75},false);
    pros::delay(300);
    chassis.setPose(0-distLeft.get()*0.0393701*cos(chassis.getPose().theta/180*3.1415926),0,chassis.getPose().theta);
    //score right long
    chassis.turnToPoint(-19,-20,500,{.forwards=false,.maxSpeed=75},true);
    chassis.moveToPoint(-19,-20,1200,{.forwards=false,.maxSpeed=110},false);
    chassis.turnToPoint(-19.5,-55,500,{.forwards=false,.maxSpeed=75},false);
    chassis.moveToPoint(-19.5,-55,1200,{.forwards=false,.maxSpeed=110},false);
    
    scoreHigh();

    chassis.setPose(0,0,chassis.getPose().theta);

    //matchload
    matchLoad.set_value(true);
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_velocity(-50);
    chassis.moveToPoint(0,50,500,{.forwards=true,.maxSpeed=100},false);
    chassis.moveToPoint(0,50,matchLoadTime,{.forwards=true,.maxSpeed=50},false);
    //pros::delay(matchLoadTime);
    chassis.setPose(18-distLeft.get()*0.0393701*cos(chassis.getPose().theta/180*3.1415926),0,chassis.getPose().theta);

    //high goal second
    chassis.moveToPoint(chassis.getPose().x,5,300,{.forwards=false,.maxSpeed=90},true);
    pros::delay(300);
    //intakeMotor.move_voltage(0);
    //outtakeMotor.move_velocity(0);
    chassis.moveToPoint(-32,-44.5,1400,{.forwards=false,.maxSpeed=90},false);
    chassis.moveToPoint(-38,-51.5,800,{.forwards=false,.maxSpeed=40},true);
    pros::delay(400);
    intakeMotor.move_velocity(-150);
    outtakeMotor.move_velocity(-600);
    pros::delay(300);
    scoreSeven();

    
    chassis.moveToPoint(-22,-35,2000,{.forwards=true,.maxSpeed=110},false);
    chassis.turnToPoint(-16,-95,1000,{.forwards=false,.maxSpeed=75},false);
    chassis.moveToPoint(-16,-100,1800,{.forwards=false,.maxSpeed=110,.minSpeed=60,.earlyExitRange=5},false);
    chassis.turnToHeading(0,400,{.maxSpeed=75},false);
    chassis.setPose(0-distLeft.get()*0.0393701*cos(chassis.getPose().theta/180*3.1415926),chassis.getPose().y,chassis.getPose().theta);
    chassis.moveToPose(-16,-103,-90,1500,{.forwards=false,.minSpeed=50,.earlyExitRange=3},true);
    chassis.turnToPoint(-16,-70,1000,{.forwards=false,.maxSpeed=75},false);
    chassis.moveToPoint(-16,-70,1200,{.forwards=false,.maxSpeed=90},true);

    scoreHigh();
    chassis.setPose(0,0,chassis.getPose().theta);

    matchLoad.set_value(true);
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_velocity(-50);
    chassis.moveToPoint(0,-50,500,{.forwards=true,.maxSpeed=100},false);
    chassis.moveToPoint(0,-50,matchLoadTime,{.forwards=true,.maxSpeed=50},false);
    //pros::delay(matchLoadTime);
    //intakeMotor.move_voltage(0);
    //outtakeMotor.move_velocity(0);
    chassis.moveToPoint(0,5,1500,{.forwards=false,.maxSpeed=70},true);
    scoreHigh();

    chassis.setPose(0,0,chassis.getPose().theta);
    matchLoad.set_value(false);
    chassis.moveToPoint(-44,-5,2000,{.forwards=true,.maxSpeed=90},false);
    chassis.turnToPoint(-45,-40,1000,{.maxSpeed=75},false);
    chassis.moveToPoint(-45,-50,1500,{.forwards=true,.minSpeed=120},true);


}

void Autonomous::skillsAuton3(){

    int matchLoadTime=2000;
    currentAngle=0;
    chassis.setPose(0,0,-90);
    originalTime = pros::millis();
    matchLoad.set_value(false);

    //intake parking
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_velocity(0);
    chassis.moveToPoint(-60,0,800,{.forwards=true,.maxSpeed=80},false);
    chassis.moveToPoint(-60,0,1500,{.forwards=true,.maxSpeed=80},false);
    
    //calibration
    chassis.turnToHeading(0,1000,{.maxSpeed=75},false);

    chassis.moveToPoint(-56,-100000,500,{.forwards=true,.maxSpeed=50},false);
    intakeMotor.move_voltage(0);
    chassis.setPose(chassis.getPose().x,7.5,chassis.getPose().theta);
    chassis.moveToPoint(chassis.getPose().x,30,1200,{.forwards=false,.maxSpeed=90},false);
    //pros::delay(300);
    chassis.setPose(distLeft.get()*0.0393701*cos(chassis.getPose().theta/180*3.1415926-3.1415926)+5,chassis.getPose().y,chassis.getPose().theta);

    //chassis.moveToPose(42,42,45,2000,{.forwards=true,.maxSpeed=90},false);
    
    //score high goal

    chassis.moveToPose(40,40,45,1000,{.forwards=true,.maxSpeed=75},false);
    intakeMotor.move_voltage(12000);
    pros::delay(300);
    intakeMotor.move_velocity(0);
    
    chassis.turnToPoint(56,56,1000,{.forwards=false,.maxSpeed=75},false);
    matchLoad.set_value(true);
    chassis.moveToPoint(56,56,1200,{.forwards=false,.maxSpeed=90},false);
    chassis.turnToPoint(64,64,600,{.forwards=false,.maxSpeed=75},false);
    pros::delay(200);
    intakeMotor.move_velocity(-150);
    outtakeMotor.move_velocity(-600);
    chassis.moveToPoint(65,65,500,{.forwards=false,.maxSpeed=90},false);
    intakeMotor.move_velocity(500);
    outtakeMotor.move_velocity(-50);
    pros::delay(700);
    intakeMotor.move_velocity(-100);
    outtakeMotor.move_velocity(-600);
    pros::delay(200);
    intakeMotor.move_velocity(500);
    outtakeMotor.move_velocity(-50);
    pros::delay(1200);
    
    //match load
    chassis.moveToPoint(25,28,1700,{.forwards=true,.maxSpeed=90},false);
    
    chassis.turnToPoint(25,5,1000,{.forwards=true,.maxSpeed=75},false);
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_velocity(-50);
    //chassis.moveToPoint(24,-50,500,{.forwards=true,.maxSpeed=100},false);

    chassis.moveToPoint(25 ,-50,matchLoadTime,{.forwards=true,.maxSpeed=50},false);
    //pros::delay(matchLoadTime);
    chassis.setPose(chassis.getPose().x,14,chassis.getPose().theta);

    

    //go score long goal
    chassis.moveToPose(16,44,180,2000,{.forwards=false,.maxSpeed=110,.minSpeed=50,.earlyExitRange=5},true);
    pros::delay(300);
    matchLoad.set_value(false);
    //intakeMotor.move_velocity(0); 
    //outtakeMotor.move_velocity(0);
    chassis.moveToPoint(17,100,1500,{.forwards=false,.maxSpeed=110,.minSpeed=60,.earlyExitRange=5},false);
    chassis.setPose(distLeft.get()*0.0393701*cos(chassis.getPose().theta/180*3.1415926-3.1415926),chassis.getPose().y,chassis.getPose().theta);
    chassis.moveToPose(23,110,-90,1500,{.forwards=false,.maxSpeed=110},false);
    chassis.turnToPoint(19,80,1000,{.forwards=false,.maxSpeed=75},false);
    chassis.moveToPoint(19,80,1500,{.forwards=false,.maxSpeed=110},true);

    //chassis.moveToPose(28,50,0,1500,{.forwards=false,.maxSpeed=60},true);
    scoreHigh();

    chassis.setPose(0,0,chassis.getPose().theta);

    //long goal second time
    matchLoad.set_value(true);
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_velocity(-50);
    chassis.moveToPoint(0,50,500,{.forwards=true,.maxSpeed=100},false);
    chassis.moveToPoint(0,50,matchLoadTime,{.forwards=true,.maxSpeed=50},false);
    //pros::delay(matchLoadTime);
    
    chassis.moveToPoint(0,-5,1200,{.forwards=false,.maxSpeed=70},true);
    pros::delay(300);
    //intakeMotor.move_voltage(0);
    //outtakeMotor.move_velocity(0);
    scoreHigh();
    matchLoad.set_value(false);
    chassis.setPose(0,0,chassis.getPose().theta);
    
    //second park zone
    //chassis.moveToPoint(18,36,500,{.forwards=true,.maxSpeed=90},false);
    chassis.moveToPoint(18,36,1500,{.forwards=true,.maxSpeed=90},false);
    //chassis.moveToPoint(25,36,1500,{.forwards=true,.maxSpeed=90},false);
    chassis.turnToHeading(70,1000,{.maxSpeed=75},false);
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_velocity(-50);
    
    chassis.moveToPose(45,42,85,500,{.forwards=true,.maxSpeed=90},false);
    pros::delay(400);
    //matchLoad.set_value(true);
    
    chassis.moveToPoint(105,42,3500,{.forwards=true,.maxSpeed=80},false);
    pros::delay(500); 
    intakeMotor.move_velocity(0);
    outtakeMotor.move_velocity(0);
    
    //matchLoad.set_value(false);

    chassis.turnToHeading(0,1000,{.maxSpeed=75},false);
    pros::delay(300);
    chassis.setPose(0-distLeft.get()*0.0393701*cos(chassis.getPose().theta/180*3.1415926),0,chassis.getPose().theta);
    //score right long
    chassis.turnToPoint(-19,-20,500,{.forwards=false,.maxSpeed=75},true);
    chassis.moveToPoint(-19,-20,1200,{.forwards=false,.maxSpeed=110},false);
    chassis.turnToPoint(-19.5,-55,500,{.forwards=false,.maxSpeed=75},false);
    chassis.moveToPoint(-19.5,-55,1200,{.forwards=false,.maxSpeed=110},false);
    
    scoreHigh();

    chassis.setPose(0,0,chassis.getPose().theta);

    //matchload
    matchLoad.set_value(true);
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_velocity(-50);
    chassis.moveToPoint(0,50,500,{.forwards=true,.maxSpeed=100},false);
    chassis.moveToPoint(0,50,matchLoadTime,{.forwards=true,.maxSpeed=50},false);
    //pros::delay(matchLoadTime);
    chassis.setPose(18-distLeft.get()*0.0393701*cos(chassis.getPose().theta/180*3.1415926),0,chassis.getPose().theta);

    //high goal second
    chassis.moveToPoint(chassis.getPose().x,5,300,{.forwards=false,.maxSpeed=90},true);
    pros::delay(300);
    //intakeMotor.move_voltage(0);
    //outtakeMotor.move_velocity(0);
    chassis.moveToPoint(-32,-44.5,1400,{.forwards=false,.maxSpeed=90},false);
    chassis.moveToPoint(-38,-51.5,800,{.forwards=false,.maxSpeed=40},true);
    pros::delay(400);
    intakeMotor.move_velocity(-150);
    outtakeMotor.move_velocity(-600);
    pros::delay(300);
    scoreSeven();

    
    chassis.moveToPoint(-22,-35,2000,{.forwards=true,.maxSpeed=110},false);
    chassis.turnToPoint(-16,-95,1000,{.forwards=false,.maxSpeed=75},false);
    chassis.moveToPoint(-16,-100,1800,{.forwards=false,.maxSpeed=110,.minSpeed=60,.earlyExitRange=5},false);
    chassis.turnToHeading(0,400,{.maxSpeed=75},false);
    chassis.setPose(0-distLeft.get()*0.0393701*cos(chassis.getPose().theta/180*3.1415926),chassis.getPose().y,chassis.getPose().theta);
    chassis.moveToPose(-16,-103,-90,1500,{.forwards=false,.minSpeed=50,.earlyExitRange=3},true);
    chassis.turnToPoint(-16,-70,1000,{.forwards=false,.maxSpeed=75},false);
    chassis.moveToPoint(-16,-70,1200,{.forwards=false,.maxSpeed=90},true);

    scoreHigh();
    chassis.setPose(0,0,chassis.getPose().theta);

    matchLoad.set_value(true);
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_velocity(-50);
    chassis.moveToPoint(0,-50,500,{.forwards=true,.maxSpeed=100},false);
    chassis.moveToPoint(0,-50,matchLoadTime,{.forwards=true,.maxSpeed=50},false);
    //pros::delay(matchLoadTime);
    //intakeMotor.move_voltage(0);
    //outtakeMotor.move_velocity(0);
    chassis.moveToPoint(0,5,1500,{.forwards=false,.maxSpeed=70},true);
    scoreHigh();

    chassis.setPose(0,0,chassis.getPose().theta);
    matchLoad.set_value(false);
    chassis.moveToPoint(-44,-5,2000,{.forwards=true,.maxSpeed=90},false);
    chassis.turnToPoint(-45,-40,1000,{.maxSpeed=75},false);
    chassis.moveToPoint(-45,-50,1500,{.forwards=true,.minSpeed=120},true);


}


void Autonomous::matchSolo(){
    currentAngle=0;
    chassis.setPose(0,0,90);
    originalTime = pros::millis();
    matchLoad.set_value(false);

    chassis.moveToPoint(28,0,1500,{.forwards=true},false);
    matchLoad.set_value(true);
    chassis.turnToHeading(180,1000,{},false);
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_velocity(-50);
    
    chassis.moveToPoint(30,-200,1000,{.forwards=true,.maxSpeed=45},false);

    //matchloading
    //pros::delay(200);
    chassis.moveToPoint(30,-25,2500,{.forwards=true,.maxSpeed=30},false);
    //pros::delay(2000);

    chassis.moveToPoint(30,22,1200,{.forwards=false,.maxSpeed=100},false);

    //scoring long goal
    outtakeMotor.move_voltage(12000);
    chassis.moveToPoint(30,27,500,{.forwards=false,.maxSpeed=100},true);
    pros::delay(1500);
    chassis.setPose(0,0,chassis.getPose().theta);
    matchLoad.set_value(false);

    //middle
    intakeMotor.move_velocity(0);
    outtakeMotor.move_velocity(0);
    chassis.moveToPoint(0,-11,1200,{.forwards=true,.maxSpeed=100},false);
    chassis.turnToPoint(-18,2,800,{.forwards=true,.maxSpeed=80},false);
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_velocity(-50);
    chassis.moveToPoint(-18,2,1000,{.forwards=true,.maxSpeed=100},false);
    matchLoad.set_value(true);

    chassis.turnToPoint(-68,2,800,{.forwards=true,.maxSpeed=80},false);
    matchLoad.set_value(false);
    chassis.moveToPoint(-68,2,1500,{.forwards=true,.maxSpeed=100},false);


    //score high goal
    chassis.turnToPoint(-52,17,1000,{.forwards=false},false);
    chassis.moveToPoint(-52,17,800,{.forwards=false},false);
    outtakeMotor.move_voltage(12000);
    pros::delay(400);

    //go to long goal
    intakeMotor.move_velocity(0);
    outtakeMotor.move_velocity(0);
    //chassis.turnToPoint(-92,-15,1000,{.forwards=true},false);
    chassis.moveToPoint(-94,-15,1200,{.forwards=true},false);

    chassis.turnToPoint(-94,5,800,{.forwards=false},false);
    chassis.moveToPoint(-94,5,800,{.forwards=false},false);

    //scoring high goal
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_voltage(12000);
    chassis.moveToPoint(-94,10,500,{.forwards=false},true);
    
    
    //color sorting
    int cDelay=10;
    std::queue<int> cRight;
    int flag=0;
    while(true){
        int temp=1;
        if (cSensor.get_hue()<45) temp=0;
        cRight.push(temp);
        if(cRight.size()>=cDelay&&cRight.front()==0){
            flag=1;
        }
        if(flag==1){
            intakeMotor.move_voltage(12000);
            outtakeMotor.move_velocity(-50);
        }
        if(flag==0){
            intakeMotor.move_voltage(12000);
            outtakeMotor.move_voltage(12000);
        }
        //back out at the end
        if (pros::millis() >= 115000 + originalTime){
            break;
        }
        pros::delay(10);
    }
    chassis.setPose(0,0,chassis.getPose().theta);

    chassis.moveToPoint(0,-15,1200,{.forwards=true},false);
    chassis.moveToPose(10,18,180,12000,{.forwards=false},false);
}









