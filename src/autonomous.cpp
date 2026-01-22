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
    chassis.turnToHeading(90,5000,{},false);
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
    chassis.moveToPoint(-62, -45, 1000, {.forwards = true, .maxSpeed = 60},false);

    pros::delay(750);
    //head to long goal
    matchLoad.set_value(false);
    chassis.moveToPoint(-30, -45, 3000, {.forwards = false, .maxSpeed = 60},false);
    outtakeMotor.move_voltage(12000);
    pros::delay(2200);
    chassis.moveToPoint(-45, -46, 2000, {.forwards = true},false);
    pros::delay(200);

    chassis.turnToHeading(320, 1000, {}, false);
    chassis.moveToPoint(-34, -54, 1000, {.forwards = false},false);
    chassis.turnToHeading(270, 800, {}, false);

    chassis.moveToPoint(-14, -54, 2000, {.forwards = false, .maxSpeed = 55},false);


}

void Autonomous::matchLeftAutonBlue(){
    currentAngle=0;
    chassis.setPose(0,0,0);
    originalTime = pros::millis();
    matchLoad.set_value(false);
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_velocity(-50);

    //turn and move to high goal
    chassis.turnToPoint(-11,22,1200,{.forwards=true},false);
    chassis.moveToPoint(-11,22,1200,{.forwards=true},false);
    matchLoad.set_value(true);
    chassis.turnToPoint(2,32,1200,{.forwards=false},false);
    chassis.moveToPoint(2,32,1200,{.forwards=false},false);

    //score high goal
    intakeMotor.move_velocity(-300);
    outtakeMotor.move_velocity(-600);
    pros::delay(200);
    intakeMotor.move_velocity(400);
    outtakeMotor.move_velocity(100);
    pros::delay(400);

    //go to matchload
    intakeMotor.move_velocity(0);
    outtakeMotor.move_velocity(0);
    pros::delay(100);
    
    chassis.moveToPoint(-32,0,1500,{.forwards=true,.maxSpeed=60},false);
    chassis.turnToPoint(-32,-19,800,{.forwards=true},false);
    
    
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_velocity(-50);
    chassis.moveToPoint(-32,-19,1500,{.forwards=true,.maxSpeed=45},false);

    //matchloading
    pros::delay(200);
    chassis.moveToPoint(-32,-100,400,{.forwards=true},false);
    
    //leaving match load
    chassis.turnToPoint(-32,25,1300,{.forwards=false},false);
    chassis.moveToPoint(-32,27,1500,{.forwards=false},false);

    //scoring long goal
    outtakeMotor.move_voltage(12000);
    chassis.moveToPoint(-32,30,500,{.forwards=false},false);

    //color sorting
    int cDelay=10;
    std::queue<int> cRight;
    int flag=0;
    while(true){
        int temp=1;
        if (cSensor.get_hue()>80) temp=0;
        cRight.push(temp);
        if(cRight.size()>=cDelay&&cRight.front()==0){
            flag=1;
        }
        if(flag==1){
            // intakeMotor.move_voltage(12000);
            // outtakeMotor.move_velocity(-50);
            intakeMotor.move_voltage(12000);
            outtakeMotor.move_voltage(12000);
        }
        if(flag==0){
            intakeMotor.move_voltage(12000);
            outtakeMotor.move_voltage(12000);
        }
        //back out at the end
        if (pros::millis() >= 11800 + originalTime){
            // drivetrain.leftMotors->move_voltage(-12000);
            // drivetrain.rightMotors->move_voltage(-12000);
            break;
        }
        pros::delay(10);
    }
    chassis.setPose(0,0,180);



    chassis.moveToPoint(0,-15,1200,{.forwards=true},false);
    chassis.moveToPose(10,18,180,12000,{.forwards=false},false);
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
    // originalTime = pros::millis();

    // chassis.setPose(0,0,-167);
    // intakeMotor.move_voltage(-3000);
    //     rampMotor.move_voltage(12000);
    //     midMotor.move_voltage(-3000);
    
    // chassis.moveToPose(5,28,167,1500,{.forwards=false},false);
    
    // // chassis.moveToPose(15,48,45,1250,{},false);
    // // intakeMotor.move_voltage(-10000);
    // //     rampMotor.move_voltage(-6000);
    // //     midMotor.move_voltage(0);
    // //     pros::delay(500);
    // // midMotor.move_voltage(10000);
    // // intakeMotor.move_voltage(10000); 
    // // rampMotor.move_voltage(12000);

    // // pros::delay(1500);
    // // midMotor.move_voltage(-5000);
    // // intakeMotor.move_voltage(-5000);
    // // rampMotor.move_voltage(0);
    // // pros::delay(500);

    // pneumatic.set_value(true);

    // chassis.moveToPoint(29.5,0,1300,{.forwards=false},false);
    // // chassis.moveToPose(-35,-25,0,750,{.forwards=false},false);
    // intakeMotor.move_voltage(-3000);
    // rampMotor.move_voltage(12000);
    // midMotor.move_voltage(-3000);
    // chassis.turnToHeading(0,1000,{},false);
    // drivetrain.leftMotors->move_voltage(-10000);
    // drivetrain.rightMotors->move_voltage(-10000);
    // pros::delay(200);
    // drivetrain.leftMotors->move_voltage(-4000);
    // drivetrain.rightMotors->move_voltage(-4000);
    // pros::delay(1100);
    // chassis.setPose(0,0,0);

    // chassis.moveToPoint(1,25,1300,{},true);
    // pros::delay(1000);
    // rampMotor.move_voltage(12000);
    // chassis.setPose(0,0,0);
    // pros::delay(300);
    // drivetrain.leftMotors->move_voltage(4000);
    // drivetrain.rightMotors->move_voltage(4000);
    // // chassis.moveToPose(0,-1,0,300,{.forwards=false},false);
    // int cDelay=3;
    // std::queue<int> cRight;
    // int countdown=0;
    // while(true){
    //     int temp=1;
    //     if (cSensor.get_hue()<455) temp=0;
    //     cRight.push(temp);
    //     if(cRight.size()>=cDelay&&cRight.front()==0){
    //         countdown=10;
    //     }
    //     if(countdown>0) countdown--;
    //     if(countdown>0){
    //         midMotor.move_voltage(10000);
    //         intakeMotor.move_voltage(2000);
    //         //midMotor.move_voltage(-10000);
    //         //intakeMotor.move_voltage(10000);
    //     }
    //     else{
    //         midMotor.move_voltage(-10000);
    //         intakeMotor.move_voltage(10000);
    //     }
    //     if(cRight.size()>=cDelay){
    //         cRight.pop();
    //     }
    //     if (pros::millis() >= 11000 + originalTime){
    //         break;
    //     }
    //     pros::delay(10);

    // }
    // intakeMotor.move_voltage(0);
    // rampMotor.move_voltage(0);
    // midMotor.move_voltage(0);
    // chassis.moveToPoint(-11.5,-10,1000,{.forwards=false},false);
    // descore.set_value(true);
    // chassis.turnToHeading(0,750,{},false);
    // chassis.moveToPose(-12,20,0,3000,{.forwards=true},false);
    
    
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
void Autonomous::skillsAuton(){
    currentAngle=0;
    chassis.setPose(0,0,90);
    originalTime = pros::millis();
    matchLoad.set_value(false);

    chassis.moveToPoint(25,0,1200,{.forwards=true},false);
    chassis.turnToPoint(25,-13,1000,{.forwards=false},false);
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_velocity(-50);
    chassis.moveToPoint(25,-13,1200,{.forwards=false},false);

    //matchloading
    pros::delay(200);
    chassis.moveToPoint(25,-10000,200,{.forwards=false},false);
    pros::delay(500);
    chassis.moveToPoint(25,13,1200,{.forwards=true},false);

    //scoring high goal
    outtakeMotor.move_voltage(12000);
    chassis.moveToPoint(25,20,500,{.forwards=true},true);
    pros::delay(1500);
    chassis.setPose(0,0,0);

    //middle
    intakeMotor.move_velocity(0);
    outtakeMotor.move_velocity(0);
    chassis.moveToPoint(0,-11,1200,{.forwards=false},false);
    chassis.turnToPoint(-20,7,1000,{.forwards=false},false);
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_velocity(-50);
    chassis.moveToPoint(-20,7,1000,{.forwards=false},false);

    chassis.turnToPoint(-66,7,1000,{.forwards=false},false);
    chassis.moveToPoint(-66,7,1500,{.forwards=false},false);

    //score high goal
    chassis.turnToPoint(-52,20,1000,{.forwards=true},false);
    chassis.moveToPoint(-52,20,1200,{.forwards=true},false);
    outtakeMotor.move_voltage(12000);
    pros::delay(1500);

    //go to long goal
    intakeMotor.move_velocity(0);
    outtakeMotor.move_velocity(0);
    chassis.turnToPoint(-90,-12,1000,{.forwards=false},false);
    chassis.moveToPoint(-90,-12,1500,{.forwards=false},false);

    chassis.turnToPoint(-90,5,1000,{.forwards=true},false);
    chassis.moveToPoint(-90,5,1500,{.forwards=true},false);

    //scoring high goal
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_voltage(12000);
    chassis.moveToPoint(-90,10,500,{.forwards=true},true);
    chassis.setPose(0,0,0);
    
    pros::delay(1000);

    

}
void Autonomous::skillsAuton2(){
    // chassis.setPose(0,0,-90);

    // chassis.moveToPose(32,0,0,2000,{.forwards=false},false);
    // chassis.turnToHeading(0,1000,{},false);

    // pneumatic.set_value(true);

    // drivetrain.leftMotors->move_voltage(-3000);
    // drivetrain.rightMotors->move_voltage(-3000);
    // intakeMotor.move_voltage(-3000);
    // rampMotor.move_voltage(12000);
    // midMotor.move_voltage(-3000);
    // pros::delay(5000);

    // chassis.moveToPose(30,50,0,2000,{},true);
    // pros::delay(1500);
    // rampMotor.move_voltage(12000);
    // midMotor.move_voltage(-10000);
    // intakeMotor.move_voltage(10000);
    // drivetrain.leftMotors->move_voltage(4000);
    // drivetrain.rightMotors->move_voltage(4000);
    // pros::delay(5000);
    // chassis.setPose(0,0,chassis.getPose().theta);
    // rampMotor.move_voltage(12000);
    // midMotor.move_voltage(-10000);
    // intakeMotor.move_voltage(10000);
    // pneumatic.set_value(false);

    // chassis.moveToPose(-33,-32,90,3000,{.forwards=false},false);
    // pneumatic.set_value(true);
    // chassis.moveToPoint(-43,-32,3000,{.forwards=false},false);
    // pneumatic.set_value(false);
    // chassis.moveToPoint(-35,-32,1500,{.forwards=true},false);
    // chassis.moveToPoint(-50,-32,1500,{.forwards=false},false);
    

    

}
void Autonomous::matchSolo(){
    currentAngle=0;
    chassis.setPose(0,0,90);
    originalTime = pros::millis();
    matchLoad.set_value(false);

    chassis.moveToPoint(25,0,1200,{.forwards=false},false);
    chassis.turnToPoint(25,-13,1000,{.forwards=true},false);
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_velocity(-50);
    chassis.moveToPoint(25,-13,1200,{.forwards=true,.maxSpeed=45},false);

    //matchloading
    pros::delay(200);
    chassis.moveToPoint(25,-10000,400,{.forwards=true},false);

    chassis.moveToPoint(25,13,1200,{.forwards=false},false);

    //scoring high goal
    outtakeMotor.move_voltage(12000);
    chassis.moveToPoint(25,20,500,{.forwards=false},true);
    pros::delay(1500);
    chassis.setPose(0,0,180);

    //middle
    intakeMotor.move_velocity(0);
    outtakeMotor.move_velocity(0);
    chassis.moveToPoint(0,-11,1200,{.forwards=true},false);
    chassis.turnToPoint(-20,7,1000,{.forwards=true},false);
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_velocity(-50);
    chassis.moveToPoint(-20,7,1000,{.forwards=true},false);

    chassis.turnToPoint(-66,7,1000,{.forwards=true},false);
    chassis.moveToPoint(-66,7,1500,{.forwards=true},false);

    //score high goal
    chassis.turnToPoint(-52,20,1000,{.forwards=false},false);
    chassis.moveToPoint(-52,20,1200,{.forwards=false},false);
    outtakeMotor.move_voltage(12000);
    pros::delay(1500);

    //go to long goal
    intakeMotor.move_velocity(0);
    outtakeMotor.move_velocity(0);
    chassis.turnToPoint(-90,-12,1000,{.forwards=true},false);
    chassis.moveToPoint(-90,-12,1500,{.forwards=true},false);

    chassis.turnToPoint(-90,5,1000,{.forwards=false},false);
    chassis.moveToPoint(-90,5,1500,{.forwards=false},false);

    //scoring high goal
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_voltage(12000);
    chassis.moveToPoint(-90,10,500,{.forwards=false},true);
    
    
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
        if (pros::millis() >= 11500 + originalTime){
            break;
        }
        pros::delay(10);
    }
    chassis.setPose(0,0,180);

    chassis.moveToPoint(0,-15,1200,{.forwards=true},false);
    chassis.moveToPose(10,18,180,12000,{.forwards=false},false);
}

