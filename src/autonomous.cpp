#include "main.h"

// const double Autonomous::CLOCKWISE_CORRECTION = 360.0 / 357.0;  // Corrects for clockwise turns
// const double Autonomous::COUNTERCLOCKWISE_CORRECTION = 357.0 / 360.0; // Corrects for counterclockwise turns

// double Autonomous::previous_heading = 0.0;
// double Autonomous::corrected_heading = 0.0;



// // class DrivetrainGood : public lemlib::Drivetrain{
// //     DrivetrainGood(lemlib::Drivetrain drivetrain) : lemlib::Drivetrain(drivetrain){}
    
// // };

double currentAngle=0;

double originalTime; 

int Autonomous::intaking=0;



void Autonomous::print(){
    while (true) {
        // print robot location to the brain screen
        pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
        pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
        pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
        // delay to save resources
        pros::delay(10);
    }
}

void Autonomous::intake(){
    if(intaking){
        intakeMotor.move_voltage(12000);
        outtakeMotor.move_velocity(-50);
        jamFlag*=0.6;
        //jamFlag+=intakeMotor.get
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

void Autonomous::distTest(){
    chassis.setPose(0,0,0, false);

    double oDist=distLeft.get()*0.0393701*cos(chassis.getPose().theta/180*3.1415926);

    //pros::lcd::initialize();
    while (true) {
        // print robot location to the brain screen
        pros::lcd::clear();
        pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
        pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
        pros::lcd::print(2, "Y: %f", distLeft.get()*0.0393701*cos(chassis.getPose().theta/180*3.1415926)-oDist);
        pros::lcd::print(3, "Theta: %f", chassis.getPose().theta); // heading
        // delay to save resources
        pros::delay(10);
    }

}

void scoreLong(){
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

void scoreLongMatch(color c=color::none,int scoringTime=1700){
    for(int i=1;i<=140;i++){
        if(distStand.get()<130){
            break;
        }
        pros::delay(10);
    }

    chassis.cancelMotion();
    leftWheels.move_voltage(-3000);
    rightWheels.move_voltage(-3000);


    originalTime = pros::millis();

    int cDelay=3;
    std::queue<int> cRight;
    int flag=0;
    while(true){
        int temp=1;

        if(c==color::red){
            if (cSensor.get_hue()>80) temp=0;
        }
        else if(c==color::blue){
            if (cSensor.get_hue()<20) temp=0;
        }

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
        if (pros::millis() >= scoringTime + originalTime){//11800
            // drivetrain.leftMotors->move_voltage(-12000);
            // drivetrain.rightMotors->move_voltage(-12000);
            break;
        }
        pros::delay(5);
    }


}

void descore(){

    matchLoad.set_value(false);
    chassis.moveToPoint(0,-15,1200,{.forwards=true,.minSpeed=30,.earlyExitRange=3},false);
    chassis.moveToPose(8.1,15,180,2000,{.forwards=false, .minSpeed=60,.earlyExitRange=10},false);
    chassis.moveToPose(10,17,180,12000,{.forwards=false, .minSpeed=90},false);

    
}




void Autonomous::matchLeft2Goal(){
    currentAngle=0;
    chassis.setPose(0,0,0);
    
    matchLoad.set_value(false);
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_velocity(-50);

    //turn and move to mid goal
    //chassis.turnToPoint(-11,22,900,{.forwards=true},false);
    //chassis.turnToPoint(-11,22,500,{.forwards=true,.maxSpeed=80},false);
    chassis.moveToPoint(-8,20,1400,{.forwards=true,.maxSpeed=90},false);
    matchLoad.set_value(true);
    //chassis.turnToPoint(5,35,1200,{.forwards=false},false);
    //chassis.turnToPoint(5,35,800,{.forwards=false,.maxSpeed=80},false);
    chassis.turnToPoint(7,36,800,{.forwards=false,.maxSpeed=80},false);
    chassis.moveToPoint(7,36,1200,{.forwards=false,.maxSpeed=110},true);

    //score mid goal
    intakeMotor.move_velocity(-300);
    outtakeMotor.move_velocity(-600);
    pros::delay(300);
    intakeMotor.move_velocity(600);
    outtakeMotor.move_velocity(0);
    pros::delay(1200);

    //go to matchload
    intakeMotor.move_velocity(0);
    outtakeMotor.move_velocity(0);
    pros::delay(100);
    
    chassis.moveToPoint(-31,0,1500,{.forwards=true,.maxSpeed=130,.minSpeed=50,.earlyExitRange=10},false);
    //chassis.turnToPoint(-34,-19,800,{.forwards=true},false);
    
    
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_velocity(-50);
    chassis.turnToHeading(180,700,{.maxSpeed=80},false);
    chassis.setPose(distLeft.get()*0.0393701*cos(chassis.getPose().theta/180*3.1415926-3.1415926),chassis.getPose().y,chassis.getPose().theta);

    chassis.moveToPoint(18,-19,700,{.forwards=true,.maxSpeed=60},false);

    //matchloading
    //pros::delay(200);
    chassis.moveToPoint(18,-100,600,{.forwards=true},true);
    //pros::delay(300);
    
    //leaving match load
    //chassis.turnToPoint(-33,25,500,{.forwards=false},false);
    chassis.moveToPoint(18.5,27,400,{.forwards=false,.maxSpeed=100},false);
    chassis.moveToPoint(18.5,27,1500,{.forwards=false,.maxSpeed=80},true);
    scoreLongMatch();

    


    chassis.setPose(0,0,chassis.getPose().theta);
    descore();

}

void Autonomous::matchLeft1Goal(){
    currentAngle=0;
    chassis.setPose(0,0,0);
    
    matchLoad.set_value(false);
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_velocity(-50);

    //turn and move to mid goal
    //chassis.turnToPoint(-11,22,900,{.forwards=true},false);
    //chassis.turnToPoint(-11,22,500,{.forwards=true,.maxSpeed=80},false);
    chassis.moveToPoint(-8,20,1400,{.forwards=true,.maxSpeed=90},false);
    matchLoad.set_value(true);
    //chassis.turnToPoint(5,35,1200,{.forwards=false},false);
    //chassis.turnToPoint(5,35,800,{.forwards=false,.maxSpeed=80},false);
    
    chassis.moveToPoint(-31,-5,1500,{.forwards=true,.maxSpeed=130,.minSpeed=50,.earlyExitRange=10},false);
    //chassis.turnToPoint(-34,-19,800,{.forwards=true},false);
    
    
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_velocity(-50);
    chassis.turnToHeading(180,700,{.maxSpeed=80},false);
    chassis.setPose(distLeft.get()*0.0393701*cos(chassis.getPose().theta/180*3.1415926-3.1415926),chassis.getPose().y,chassis.getPose().theta);

    chassis.moveToPoint(18,-19,700,{.forwards=true,.maxSpeed=60},false);

    //matchloading
    //pros::delay(200);
    chassis.moveToPoint(18,-100,600,{.forwards=true},true);
    //pros::delay(300);
    
    //leaving match load
    //chassis.turnToPoint(-33,25,500,{.forwards=false},false);
    chassis.moveToPoint(18.5,27,400,{.forwards=false,.maxSpeed=100},false);
    chassis.moveToPoint(18.5,27,1500,{.forwards=false,.maxSpeed=80},true);
    scoreLongMatch();

    


    chassis.setPose(0,0,chassis.getPose().theta);
    descore();


}



void Autonomous::matchRight2Goal(){
    chassis.setPose(0,0,0);
    
    matchLoad.set_value(false);
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_velocity(0);


    chassis.turnToPoint(10,21,700,{.forwards=true,.maxSpeed=75},false);
    chassis.moveToPoint(10,21,1200,{.forwards=true,.maxSpeed=90,.minSpeed=90,.earlyExitRange=10},false);
    matchLoad.set_value(true);
    chassis.moveToPoint(10,21,1200,{.forwards=true,.maxSpeed=50},false);
    matchLoad.set_value(false);
    chassis.turnToPoint(-4,31,800,{.forwards=true,.maxSpeed=75},false);
    middleDescore.set_value(true);
    chassis.moveToPoint(-4,31,1100,{.forwards=true,.maxSpeed=90},false);
    intakeMotor.move_velocity(-400);
    pros::delay(900);


    intakeMotor.move_velocity(0);
    matchLoad.set_value(true);
    middleDescore.set_value(false);
    chassis.moveToPoint(33,0,1200,{.forwards=false,.maxSpeed=90,.minSpeed=30,.earlyExitRange=3},false);
    chassis.turnToPoint(33,-20,1500,{.forwards=true,.maxSpeed=75},false);
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_velocity(-50);
    chassis.moveToPoint(33,-25,1200,{.forwards=true,.maxSpeed=50},true);
    pros::delay(1200);
    chassis.moveToPoint(33,20,1200,{.forwards=false,.maxSpeed=90},true);
    scoreLongMatch();

    chassis.setPose(0,0,chassis.getPose().theta);
    descore();

    // matchLoad.set_value(false);
    // chassis.moveToPoint(0, -16, 1200, {.forwards = true,.minSpeed=30,.earlyExitRange=3},false);
    // chassis.moveToPose(8.2, 16, 180, 10000, {.forwards = false,.minSpeed=70},false);
    // rightWheels.move_velocity(0);
    // leftWheels.move_velocity(0);

}

void Autonomous::matchRight1Goal(){
    chassis.setPose(0,0,0);
    
    matchLoad.set_value(false);
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_velocity(0);


    chassis.turnToPoint(10,21,700,{.forwards=true,.maxSpeed=75},false);
    chassis.moveToPoint(10,21,1200,{.forwards=true,.maxSpeed=90,.minSpeed=90,.earlyExitRange=10},false);
    matchLoad.set_value(true);
    chassis.moveToPoint(10,21,1200,{.forwards=true,.maxSpeed=50},false);
    

    chassis.moveToPoint(34,0,1400,{.forwards=false,.maxSpeed=90,.minSpeed=30,.earlyExitRange=3},false);
    chassis.turnToPoint(34,-20,1500,{.forwards=true,.maxSpeed=75},false);
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_velocity(-50);
    chassis.moveToPoint(35,-25,1200,{.forwards=true,.maxSpeed=50},true);
    pros::delay(1000);
    chassis.moveToPoint(35,20,1200,{.forwards=false,.maxSpeed=90},true);
    scoreLongMatch(color::blue);

    chassis.setPose(0,0,chassis.getPose().theta);
    descore();
}


void Autonomous::matchSolo(){
    currentAngle=0;
    chassis.setPose(2.5,0,-90);
    originalTime = pros::millis();
    matchLoad.set_value(false);

    intakeMotor.move_voltage(12000);
    outtakeMotor.move_velocity(-50);

    chassis.moveToPoint(-5,0,500,{.forwards=true},false);
    chassis.moveToPoint(48,0,1500,{.forwards=false},false);
    matchLoad.set_value(true);
    chassis.turnToPoint(48,-25,1200,{.forwards=true,.maxSpeed=80},false);
    

    //matchloading
    //pros::delay(200);
    chassis.moveToPoint(48,-25,900,{.forwards=true,.maxSpeed=50},false);
    //pros::delay(2000);

    chassis.moveToPoint(51,22,1200,{.forwards=false,.maxSpeed=130},true);

    //scoring long goal
    //outtakeMotor.move_voltage(12000);
    //chassis.moveToPoint(51,27,500,{.forwards=false,.maxSpeed=100},true);
    //pros::delay(1500);
    
    scoreLongMatch(color::none,1500);
    chassis.setPose(0,0,chassis.getPose().theta);
    matchLoad.set_value(false);
    

    //middle
    intakeMotor.move_velocity(0);
    outtakeMotor.move_velocity(-50);
    //chassis.moveToPoint(0,-11,1200,{.forwards=true,.maxSpeed=100},false);
    chassis.moveToPoint(-16,4,1000,{.forwards=true,.maxSpeed=80,.minSpeed=30,.earlyExitRange=8},false);
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_velocity(-50);
    //chassis.moveToPoint(-16,2,1000,{.forwards=true,.maxSpeed=100},false);
    
    //chassis.turnToPoint(-68,1,800,{.forwards=true,.maxSpeed=80},false);
    
    chassis.moveToPoint(-68,0,1500,{.forwards=true,.maxSpeed=120,.minSpeed=30,.earlyExitRange=12.5},false);
    matchLoad.set_value(true);
    chassis.moveToPoint(-68,0,500,{.forwards=true,.maxSpeed=80},false);
    


    //score high goal
    chassis.turnToPoint(-48.5,16,1000,{.forwards=false,.maxSpeed=80},false);
    
    chassis.moveToPoint(-48.5,16,1000,{.forwards=false,.maxSpeed=80},true);
    intakeMotor.move_velocity(-180);
    outtakeMotor.move_velocity(-600);
    pros::delay(300);
    intakeMotor.move_velocity(0);
    outtakeMotor.move_velocity(0);
    pros::delay(100);
    intakeMotor.move_velocity(450);
    outtakeMotor.move_velocity(0);
    pros::delay(1000);

    //go to long goal
    intakeMotor.move_velocity(0);
    outtakeMotor.move_velocity(-50);
    //chassis.turnToPoint(-92,-15,1000,{.forwards=true},false);
    chassis.moveToPoint(-86,-17,1200,{.forwards=true,.maxSpeed=100},false);

    chassis.turnToPoint(-88,-45,800,{.forwards=true,.maxSpeed=80},false);
    chassis.setPose(distLeft.get()*0.0393701*cos(chassis.getPose().theta/180*3.1415926-3.1415926),chassis.getPose().y,chassis.getPose().theta);
    intakeMotor.move_voltage(12000);
    chassis.moveToPoint(18,-45,1000,{.forwards=true,.maxSpeed=70,.minSpeed=30,.earlyExitRange=20},false);
    chassis.moveToPoint(18,-45,1000,{.forwards=true,.maxSpeed=60,.minSpeed=30,.earlyExitRange=15},false);
    chassis.moveToPoint(18,-45,800,{.forwards=true,.maxSpeed=40},false);

    chassis.moveToPoint(17.5,20,1200,{.forwards=false,.maxSpeed=100},true);

    scoreLongMatch(color::none,15000);
    

    descore();
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
    for(int i=1;i<=130;i++){
        if(cSensor2.get_hue()<30){
            pros::delay(50);
            break;
        }
        pros::delay(10);
    }
    intakeMotor.move_velocity(0);
    outtakeMotor.move_velocity(0);
}

void matchload(){
    for(int i=1;i<=140;i++){
        if(distFront.get()<300){
            break;
            chassis.cancelMotion();
        }
        pros::delay(10);
    }

    rightWheels.move_voltage(-6000);
    leftWheels.move_voltage(-6000);
    pros::delay(1800);
}


void Autonomous::skillsAuton2(){

    int matchLoadTime=2000;
    currentAngle=0;
    chassis.setPose(0,0,-90);
    originalTime = pros::millis();
    matchLoad.set_value(false);

    //intake parking
    intakeMotor.move_voltage(12000);
    outtakeMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    outtakeMotor.move_velocity(0);
    chassis.moveToPoint(-60,0,300,{.forwards=true,.maxSpeed=70},false);
    matchLoad.set_value(true);
    pros::delay(500);
    matchLoad.set_value(false);
    chassis.moveToPoint(-60,0,1700,{.forwards=true,.maxSpeed=80},true);

    //calibration
    chassis.turnToHeading(180,1000,{.maxSpeed=75},false);

    //chassis.moveToPoint(-56,-100000,500,{.forwards=true,.maxSpeed=50},false);
    intakeMotor.move_voltage(0);
    chassis.setPose(chassis.getPose().x,10,chassis.getPose().theta);
    //chassis.moveToPoint(chassis.getPose().x,30,1200,{.forwards=false,.maxSpeed=90},false);
    //pros::delay(300);
    chassis.setPose(distLeft.get()*0.0393701*cos(chassis.getPose().theta/180*3.1415926-3.1415926)+5,distFront.get()*0.0393701*cos(chassis.getPose().theta/180*3.1415926-3.1415926)+9.4 ,chassis.getPose().theta);

    //chassis.moveToPose(42,42,45,2000,{.forwards=true,.maxSpeed=90},false);

    //score high goal
    chassis.turnToPoint(56,56,1000,{.forwards=false,.maxSpeed=75},false);
    matchLoad.set_value(true);
    chassis.moveToPoint(56,56,1500,{.forwards=false,.maxSpeed=90},false);
    chassis.turnToPoint(66,66,600,{.forwards=false,.maxSpeed=75},false);
    pros::delay(200);
    intakeMotor.move_velocity(-250);
    outtakeMotor.move_velocity(0);
    chassis.moveToPoint(65,65,500,{.forwards=false,.maxSpeed=90},false);
    intakeMotor.move_velocity(450);
    outtakeMotor.move_velocity(0);
    pros::delay(1100);
    intakeMotor.move_velocity(-200);
    outtakeMotor.move_velocity(-600);
    pros::delay(200);
    intakeMotor.move_velocity(550);
    outtakeMotor.move_velocity(0);
    pros::delay(1200);

    outtakeMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

    //match load
    outtakeMotor.move_velocity(600);
    intakeMotor.move_velocity(600);
    chassis.moveToPoint(26,28,1700,{.forwards=true,.maxSpeed=90},false);

    chassis.turnToPoint(26,5,1000,{.forwards=true,.maxSpeed=75},false);
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_velocity(-50);
    //chassis.moveToPoint(24,-50,500,{.forwards=true,.maxSpeed=100},false);

    chassis.moveToPoint(25 ,-50,matchLoadTime,{.forwards=true,.maxSpeed=50},true);
    matchload();
    //pros::delay(matchLoadTime);
    chassis.setPose(chassis.getPose().x,14,chassis.getPose().theta);



    //go score long goal
    chassis.moveToPose(16,44,180,2000,{.forwards=false,.maxSpeed=110,.minSpeed=50,.earlyExitRange=5},true);
    pros::delay(300);
    matchLoad.set_value(false);
    intakeMotor.move_velocity(200); 
    outtakeMotor.move_velocity(0);
    chassis.moveToPoint(17,100,1500,{.forwards=false,.maxSpeed=110,.minSpeed=60,.earlyExitRange=5},false);
    chassis.setPose(distLeft.get()*0.0393701*cos(chassis.getPose().theta/180*3.1415926-3.1415926),chassis.getPose().y,chassis.getPose().theta);
    chassis.moveToPose(23,110,-90,1500,{.forwards=false,.maxSpeed=110},false);
    chassis.turnToPoint(19,80,1000,{.forwards=false,.maxSpeed=75},false);
    chassis.moveToPoint(19,80,1500,{.forwards=false,.maxSpeed=110},true);

    //chassis.moveToPose(28,50,0,1500,{.forwards=false,.maxSpeed=60},true);
    scoreLong();

    chassis.setPose(0,0,chassis.getPose().theta);

    //long goal second time
    matchLoad.set_value(true);
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_velocity(-50);
    chassis.moveToPoint(1,50,500,{.forwards=true,.maxSpeed=100},false);
    chassis.moveToPoint(1,50,matchLoadTime,{.forwards=true,.maxSpeed=50},true);
    matchload();
    //pros::delay(matchLoadTime);

    chassis.moveToPoint(0,-5,1200,{.forwards=false,.maxSpeed=70},true);
    pros::delay(300);
    //intakeMotor.move_voltage(0);
    //outtakeMotor.move_velocity(0);
    scoreLong();
    matchLoad.set_value(false);
    chassis.setPose(0,0,chassis.getPose().theta);

    chassis.moveToPoint(0,3,400,{.forwards=true,.maxSpeed=80},true);
    chassis.moveToPoint(0,-2,400,{.forwards=false,.maxSpeed=50},true);
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

    chassis.moveToPoint(95,42,2500,{.forwards=true,.maxSpeed=80},true);
    pros::delay(500);
    matchLoad.set_value(true);
    pros::delay(500);
    matchLoad.set_value(false);
    chassis.moveToPoint(95,42,30,{.forwards=true,.maxSpeed=80},false);
    pros::delay(500); 
    intakeMotor.move_velocity(0);
    outtakeMotor.move_velocity(0);

    //matchLoad.set_value(false);

    chassis.turnToHeading(0,1000,{.maxSpeed=75},false);
    pros::delay(300);
    chassis.setPose(0-distLeft.get()*0.0393701*cos(chassis.getPose().theta/180*3.1415926),0,chassis.getPose().theta);
    //score right long
    chassis.turnToPoint(-18.5,-20,500,{.forwards=false,.maxSpeed=75},true);
    chassis.moveToPoint(-18.5,-20,1200,{.forwards=false,.maxSpeed=110},false);
    chassis.turnToPoint(-19,-55,500,{.forwards=false,.maxSpeed=75},false);
    chassis.moveToPoint(-19,-55,1200,{.forwards=false,.maxSpeed=110},false);

    scoreLong();

    chassis.setPose(0,0,chassis.getPose().theta);

    //matchload
    matchLoad.set_value(true);
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_velocity(-50);
    chassis.moveToPoint(0,50,500,{.forwards=true,.maxSpeed=100},false);
    chassis.moveToPoint(0,50,matchLoadTime,{.forwards=true,.maxSpeed=50},true);
    matchload();
    //pros::delay(matchLoadTime);
    chassis.setPose(18-distLeft.get()*0.0393701*cos(chassis.getPose().theta/180*3.1415926),0,chassis.getPose().theta);

    chassis.moveToPoint(chassis.getPose().x,-8,500,{.forwards=false,.maxSpeed=90},false);
    intakeMotor.move_voltage(0);
    pros::delay(300);
    chassis.setPose(18-distLeft.get()*0.0393701*cos(chassis.getPose().theta/180*3.1415926),
                    5.5-distFront.get()*0.0393701*cos(chassis.getPose().theta/180*3.1415926),
                    chassis.getPose().theta);


    //high goal second
    //chassis.moveToPoint(chassis.getPose().x,5,300,{.forwards=false,.maxSpeed=90},true);
    //pros::delay(300);
    //intakeMotor.move_voltage(0);
    //outtakeMotor.move_velocity(0);
    chassis.moveToPoint(-26,-40 ,1400,{.forwards=false,.maxSpeed=90},false);
    chassis.turnToPoint(-38,-52,800,{.forwards=false,.maxSpeed=80},true);
    chassis.moveToPoint(-38,-52,800,{.forwards=false,.maxSpeed=40},true);
    pros::delay(400);
    intakeMotor.move_velocity(-300);
    outtakeMotor.move_velocity(-600);
    pros::delay(300);
    scoreSeven();

 
    chassis.moveToPoint(-22,-35,2000,{.forwards=true,.maxSpeed=110},false);
    chassis.turnToPoint(-16,-95,1000,{.forwards=false,.maxSpeed=75},false);
    chassis.moveToPoint(-16,-100,1800,{.forwards=false,.maxSpeed=110,.minSpeed=60,.earlyExitRange=5},false);
    chassis.turnToHeading(0,400,{.maxSpeed=75},false);
    chassis.setPose(0-distLeft.get()*0.0393701*cos(chassis.getPose().theta/180*3.1415926),chassis.getPose().y,chassis.getPose().theta);
    chassis.moveToPose(-16,-103,-90,1500,{.forwards=false,.minSpeed=50,.earlyExitRange=3},true);
    chassis.turnToPoint(-18,-70,1000,{.forwards=false,.maxSpeed=75},false);
    chassis.moveToPoint(-18,-70,1200,{.forwards=false,.maxSpeed=90},true);

    scoreLong();
    chassis.setPose(0,0,chassis.getPose().theta);

    matchLoad.set_value(true);
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_velocity(-50);
    chassis.moveToPoint(-1,-50,500,{.forwards=true,.maxSpeed=100},false);
    chassis.moveToPoint(-1,-50,matchLoadTime,{.forwards=true,.maxSpeed=50},true);
    matchload();
    //pros::delay(matchLoadTime);
    //intakeMotor.move_voltage(0);
    //outtakeMotor.move_velocity(0);
    chassis.moveToPoint(0,5,1500,{.forwards=false,.maxSpeed=70},true);
    scoreLong();

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

    chassis.moveToPoint(-56,-100000,500,{.forwards=false,.maxSpeed=50},false);
    intakeMotor.move_voltage(0);
    chassis.setPose(chassis.getPose().x,7.5,chassis.getPose().theta);
    //chassis.moveToPoint(chassis.getPose().x,20,1200,{.forwards=true,.maxSpeed=90},false);
    //pros::delay(300);
    chassis.setPose(distRight.get()*0.0393701*cos(chassis.getPose().theta/180*3.1415926)+5,chassis.getPose().y,chassis.getPose().theta);

    //pros::delay(100000000);

    //chassis.moveToPose(42,42,45,2000,{.forwards=true,.maxSpeed=90},false);
    
    //score high goal

    chassis.moveToPoint(chassis.getPose().x,chassis.getPose().x,1000,{.forwards=true,.maxSpeed=90},false);
    chassis.turnToPoint(43.5,43.5,800,{.forwards=true,.maxSpeed=75},false);
    chassis.moveToPoint(43.5,43.5,1200,{.forwards=true,.maxSpeed=90},false);

    //chassis.moveToPose(41,41,45,1500,{.forwards=true,.maxSpeed=75},false);
    intakeMotor.move_voltage(12000);
    pros::delay(300);
    intakeMotor.move_velocity(0);
    
    chassis.turnToPoint(60,60,1000,{.forwards=false,.maxSpeed=75},false);
    matchLoad.set_value(true);
    chassis.moveToPoint(60,60,1200,{.forwards=false,.maxSpeed=90,.minSpeed=60,.earlyExitRange=5},false);
    //chassis.turnToPoint(66,66,600,{.forwards=false,.maxSpeed=75},false);
    
    
    chassis.moveToPoint(66,66,500,{.forwards=false,.maxSpeed=90},false);
    
    intakeMotor.move_velocity(-150);
    outtakeMotor.move_velocity(0);
    pros::delay(200);
    intakeMotor.move_velocity(500);
    outtakeMotor.move_velocity(0);
    pros::delay(700);
    intakeMotor.move_velocity(-100);
    outtakeMotor.move_velocity(0);
    pros::delay(200);
    intakeMotor.move_velocity(500);
    outtakeMotor.move_velocity(0);
    pros::delay(1200);
    
    //match load
    chassis.moveToPoint(27,28,1700,{.forwards=true,.maxSpeed=90},false);
    
    chassis.turnToPoint(27,5,1000,{.forwards=true,.maxSpeed=75},false);
    intakeMotor.move_voltage(12000);
    outtakeMotor.move_velocity(0);
    //chassis.moveToPoint(24,-50,500,{.forwards=true,.maxSpeed=100},false);

    chassis.moveToPoint(27 ,-50,matchLoadTime,{.forwards=true,.maxSpeed=50},false);
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
    scoreLong();

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
    scoreLong();
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
    
    scoreLong();

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

    scoreLong();
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
    scoreLong();

    chassis.setPose(0,0,chassis.getPose().theta);
    matchLoad.set_value(false);
    chassis.moveToPoint(-44,-5,2000,{.forwards=true,.maxSpeed=90},false);
    chassis.turnToPoint(-45,-40,1000,{.maxSpeed=75},false);
    chassis.moveToPoint(-45,-50,1500,{.forwards=true,.minSpeed=120},true);


}


