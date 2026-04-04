// #include "main.h"

// void Autonomous::skillsAuton2(){

//     int matchLoadTime=2000;
//     currentAngle=0;
//     chassis.setPose(0,0,-90);
//     originalTime = pros::millis();
//     matchLoad.set_value(false);

//     //intake parking
//     intakeMotor.move_voltage(12000);
//     outtakeMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
//     outtakeMotor.move_velocity(0);
//     chassis.moveToPoint(-60,0,600,{.forwards=true,.maxSpeed=70},false);
//     chassis.moveToPoint(-60,0,1700,{.forwards=true,.maxSpeed=80},true);

//     matchLoad.set_value(true);
//     pros::delay(500);
//     matchLoad.set_value(false);
    
//     //calibration
//     chassis.turnToHeading(180,1000,{.maxSpeed=75},false);

//     //chassis.moveToPoint(-56,-100000,500,{.forwards=true,.maxSpeed=50},false);
//     intakeMotor.move_voltage(0);
//     chassis.setPose(chassis.getPose().x,10,chassis.getPose().theta);
//     //chassis.moveToPoint(chassis.getPose().x,30,1200,{.forwards=false,.maxSpeed=90},false);
//     //pros::delay(300);
//     chassis.setPose(distLeft.get()*0.0393701*cos(chassis.getPose().theta/180*3.1415926-3.1415926)+5,distFront.get()*0.0393701*cos(chassis.getPose().theta/180*3.1415926-3.1415926)+9.4 ,chassis.getPose().theta);

//     //chassis.moveToPose(42,42,45,2000,{.forwards=true,.maxSpeed=90},false);

//     //score high goal
//     chassis.turnToPoint(56,56,1000,{.forwards=false,.maxSpeed=75},false);
//     matchLoad.set_value(true);
//     chassis.moveToPoint(56,56,1500,{.forwards=false,.maxSpeed=90},false);
//     chassis.turnToPoint(66,66,600,{.forwards=false,.maxSpeed=75},false);
//     pros::delay(200);
//     intakeMotor.move_velocity(-200);
//     outtakeMotor.move_velocity(-600);
//     chassis.moveToPoint(65,65,500,{.forwards=false,.maxSpeed=90},false);
//     intakeMotor.move_velocity(450);
//     outtakeMotor.move_velocity(0);
//     pros::delay(1100);
//     intakeMotor.move_velocity(-150);
//     outtakeMotor.move_velocity(-600);
//     pros::delay(200);
//     intakeMotor.move_velocity(550);
//     outtakeMotor.move_velocity(0);
//     pros::delay(1200);

//     outtakeMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

//     //match load
//     outtakeMotor.move_velocity(600);
//     intakeMotor.move_velocity(600);
//     chassis.moveToPoint(26,28,1700,{.forwards=true,.maxSpeed=90},false);

//     chassis.turnToPoint(26,5,1000,{.forwards=true,.maxSpeed=75},false);
//     intakeMotor.move_voltage(12000);
//     outtakeMotor.move_velocity(-50);
//     //chassis.moveToPoint(24,-50,500,{.forwards=true,.maxSpeed=100},false);

//     chassis.moveToPoint(25 ,-50,matchLoadTime,{.forwards=true,.maxSpeed=50},true);
//     matchload();
//     //pros::delay(matchLoadTime);
//     chassis.setPose(chassis.getPose().x,14,chassis.getPose().theta);



//     //go score long goal
//     chassis.moveToPose(16,44,180,2000,{.forwards=false,.maxSpeed=110,.minSpeed=50,.earlyExitRange=5},true);
//     pros::delay(300);
//     matchLoad.set_value(false);
//     intakeMotor.move_velocity(200); 
//     outtakeMotor.move_velocity(0);
//     chassis.moveToPoint(17,100,1500,{.forwards=false,.maxSpeed=110,.minSpeed=60,.earlyExitRange=5},false);
//     chassis.setPose(distLeft.get()*0.0393701*cos(chassis.getPose().theta/180*3.1415926-3.1415926),chassis.getPose().y,chassis.getPose().theta);
//     chassis.moveToPose(23,110,-90,1500,{.forwards=false,.maxSpeed=110},false);
//     chassis.turnToPoint(19,80,1000,{.forwards=false,.maxSpeed=75},false);
//     chassis.moveToPoint(19,80,1500,{.forwards=false,.maxSpeed=110},true);

//     //chassis.moveToPose(28,50,0,1500,{.forwards=false,.maxSpeed=60},true);
//     scoreLong();

//     chassis.setPose(0,0,chassis.getPose().theta);

//     //long goal second time
//     matchLoad.set_value(true);
//     intakeMotor.move_voltage(12000);
//     outtakeMotor.move_velocity(-50);
//     chassis.moveToPoint(1,50,500,{.forwards=true,.maxSpeed=100},false);
//     chassis.moveToPoint(1,50,matchLoadTime,{.forwards=true,.maxSpeed=50},true);
//     matchload();
//     //pros::delay(matchLoadTime);

//     chassis.moveToPoint(0,-5,1200,{.forwards=false,.maxSpeed=70},true);
//     pros::delay(300);
//     //intakeMotor.move_voltage(0);
//     //outtakeMotor.move_velocity(0);
//     scoreLong();
//     matchLoad.set_value(false);
//     chassis.setPose(0,0,chassis.getPose().theta);

//     chassis.moveToPoint(0,3,400,{.forwards=true,.maxSpeed=80},true);
//     chassis.moveToPoint(0,-2,400,{.forwards=false,.maxSpeed=50},true);
//     chassis.setPose(0,0,chassis.getPose().theta);

//     //second park zone
//     //chassis.moveToPoint(18,36,500,{.forwards=true,.maxSpeed=90},false);
//     chassis.moveToPoint(18,36,1500,{.forwards=true,.maxSpeed=90},false);
//     //chassis.moveToPoint(25,36,1500,{.forwards=true,.maxSpeed=90},false);
//     chassis.turnToHeading(70,1000,{.maxSpeed=75},false);
//     intakeMotor.move_voltage(12000);
//     outtakeMotor.move_velocity(-50);
    

//     chassis.moveToPose(45,42,85,500,{.forwards=true,.maxSpeed=90},false);
//     pros::delay(400);
//     //matchLoad.set_value(true);

//     chassis.moveToPoint(95,42,2500,{.forwards=true,.maxSpeed=80},true);
//     pros::delay(500);
//     matchLoad.set_value(true);
//     pros::delay(500);
//     matchLoad.set_value(false);
//     chassis.moveToPoint(95,42,30,{.forwards=true,.maxSpeed=80},false);
//     pros::delay(500); 
//     intakeMotor.move_velocity(0);
//     outtakeMotor.move_velocity(0);

//     //matchLoad.set_value(false);

//     chassis.turnToHeading(0,1000,{.maxSpeed=75},false);
//     pros::delay(300);
//     chassis.setPose(0-distLeft.get()*0.0393701*cos(chassis.getPose().theta/180*3.1415926),0,chassis.getPose().theta);
//     //score right long
//     chassis.turnToPoint(-18.5,-20,500,{.forwards=false,.maxSpeed=75},true);
//     chassis.moveToPoint(-18.5,-20,1200,{.forwards=false,.maxSpeed=110},false);
//     chassis.turnToPoint(-19,-55,500,{.forwards=false,.maxSpeed=75},false);
//     chassis.moveToPoint(-19,-55,1200,{.forwards=false,.maxSpeed=110},false);

//     scoreLong();

//     chassis.setPose(0,0,chassis.getPose().theta);

//     //matchload
//     matchLoad.set_value(true);
//     intakeMotor.move_voltage(12000);
//     outtakeMotor.move_velocity(-50);
//     chassis.moveToPoint(0,50,500,{.forwards=true,.maxSpeed=100},false);
//     chassis.moveToPoint(0,50,matchLoadTime,{.forwards=true,.maxSpeed=50},true);
//     matchload();
//     //pros::delay(matchLoadTime);
//     chassis.setPose(18-distLeft.get()*0.0393701*cos(chassis.getPose().theta/180*3.1415926),0,chassis.getPose().theta);

//     chassis.moveToPoint(chassis.getPose().x,-8,500,{.forwards=false,.maxSpeed=90},false);
//     intakeMotor.move_voltage(0);
//     pros::delay(300);
//     chassis.setPose(18-distLeft.get()*0.0393701*cos(chassis.getPose().theta/180*3.1415926),
//                     5.5-distFront.get()*0.0393701*cos(chassis.getPose().theta/180*3.1415926),
//                     chassis.getPose().theta);


//     intakeMotor.move_velocity(50);

//     //high goal second
//     //chassis.moveToPoint(chassis.getPose().x,5,300,{.forwards=false,.maxSpeed=90},true);
//     //pros::delay(300);
//     //intakeMotor.move_voltage(0);
//     //outtakeMotor.move_velocity(0);
//     chassis.moveToPoint(-26,-40 ,1400,{.forwards=false,.maxSpeed=90},false);
//     chassis.turnToPoint(-38,-52,800,{.forwards=false,.maxSpeed=80},true);
//     chassis.moveToPoint(-38,-52,800,{.forwards=false,.maxSpeed=40},true);
//     pros::delay(400);
//     intakeMotor.move_velocity(-300);
//     outtakeMotor.move_velocity(-600);
//     pros::delay(300);
//     scoreSeven();

 
//     chassis.moveToPoint(-22,-35,2000,{.forwards=true,.maxSpeed=110},false);
//     chassis.turnToPoint(-16,-95,1000,{.forwards=false,.maxSpeed=75},false);
//     chassis.moveToPoint(-16,-100,1800,{.forwards=false,.maxSpeed=110,.minSpeed=60,.earlyExitRange=5},false);
//     chassis.turnToHeading(0,400,{.maxSpeed=75},false);
//     chassis.setPose(0-distLeft.get()*0.0393701*cos(chassis.getPose().theta/180*3.1415926),chassis.getPose().y,chassis.getPose().theta);
//     chassis.moveToPose(-16,-103,-90,1500,{.forwards=false,.minSpeed=50,.earlyExitRange=3},true);
//     chassis.turnToPoint(-18,-70,1000,{.forwards=false,.maxSpeed=75},false);
//     chassis.moveToPoint(-18,-70,1200,{.forwards=false,.maxSpeed=90},true);

//     scoreLong();
//     chassis.setPose(0,0,chassis.getPose().theta);

//     matchLoad.set_value(true);
//     intakeMotor.move_voltage(12000);
//     outtakeMotor.move_velocity(-50);
//     chassis.moveToPoint(-1,-50,500,{.forwards=true,.maxSpeed=100},false);
//     chassis.moveToPoint(-1,-50,matchLoadTime,{.forwards=true,.maxSpeed=50},true);
//     matchload();
//     //pros::delay(matchLoadTime);
//     //intakeMotor.move_voltage(0);
//     //outtakeMotor.move_velocity(0);
//     chassis.moveToPoint(0,5,1500,{.forwards=false,.maxSpeed=70},true);
//     scoreLong();

//     chassis.setPose(0,0,chassis.getPose().theta);
//     matchLoad.set_value(false);
//     chassis.moveToPoint(-44,-5,2000,{.forwards=true,.maxSpeed=90},false);
//     chassis.turnToPoint(-45,-40,1000,{.maxSpeed=75},false);
//     chassis.moveToPoint(-45,-50,1500,{.forwards=true,.minSpeed=120},true);


// }

// void Autonomous::skillsAuton3(){

//     int matchLoadTime=2000;
//     currentAngle=0;
//     chassis.setPose(0,0,-90);
//     originalTime = pros::millis();
//     matchLoad.set_value(false);

//     //intake parking
//     intakeMotor.move_voltage(12000);
//     outtakeMotor.move_velocity(0);
//     chassis.moveToPoint(-60,0,800,{.forwards=true,.maxSpeed=80},false);
//     chassis.moveToPoint(-60,0,1500,{.forwards=true,.maxSpeed=80},false);
    
//     //calibration
//     chassis.turnToHeading(0,1000,{.maxSpeed=75},false);

//     chassis.moveToPoint(-56,-100000,500,{.forwards=false,.maxSpeed=50},false);
//     intakeMotor.move_voltage(0);
//     chassis.setPose(chassis.getPose().x,7.5,chassis.getPose().theta);
//     //chassis.moveToPoint(chassis.getPose().x,20,1200,{.forwards=true,.maxSpeed=90},false);
//     //pros::delay(300);
//     chassis.setPose(distRight.get()*0.0393701*cos(chassis.getPose().theta/180*3.1415926)+5,chassis.getPose().y,chassis.getPose().theta);

//     //pros::delay(100000000);

//     //chassis.moveToPose(42,42,45,2000,{.forwards=true,.maxSpeed=90},false);
    
//     //score high goal

//     chassis.moveToPoint(chassis.getPose().x,chassis.getPose().x,1000,{.forwards=true,.maxSpeed=90},false);
//     chassis.turnToPoint(43.5,43.5,800,{.forwards=true,.maxSpeed=75},false);
//     chassis.moveToPoint(43.5,43.5,1200,{.forwards=true,.maxSpeed=90},false);

//     //chassis.moveToPose(41,41,45,1500,{.forwards=true,.maxSpeed=75},false);
//     intakeMotor.move_voltage(12000);
//     pros::delay(300);
//     intakeMotor.move_velocity(0);
    
//     chassis.turnToPoint(60,60,1000,{.forwards=false,.maxSpeed=75},false);
//     matchLoad.set_value(true);
//     chassis.moveToPoint(60,60,1200,{.forwards=false,.maxSpeed=90,.minSpeed=60,.earlyExitRange=5},false);
//     //chassis.turnToPoint(66,66,600,{.forwards=false,.maxSpeed=75},false);
    
    
//     chassis.moveToPoint(66,66,500,{.forwards=false,.maxSpeed=90},false);
    
//     intakeMotor.move_velocity(-150);
//     outtakeMotor.move_velocity(0);
//     pros::delay(200);
//     intakeMotor.move_velocity(500);
//     outtakeMotor.move_velocity(0);
//     pros::delay(700);
//     intakeMotor.move_velocity(-100);
//     outtakeMotor.move_velocity(0);
//     pros::delay(200);
//     intakeMotor.move_velocity(500);
//     outtakeMotor.move_velocity(0);
//     pros::delay(1200);
    
//     //match load
//     chassis.moveToPoint(27,28,1700,{.forwards=true,.maxSpeed=90},false);
    
//     chassis.turnToPoint(27,5,1000,{.forwards=true,.maxSpeed=75},false);
//     intakeMotor.move_voltage(12000);
//     outtakeMotor.move_velocity(0);
//     //chassis.moveToPoint(24,-50,500,{.forwards=true,.maxSpeed=100},false);

//     chassis.moveToPoint(27 ,-50,matchLoadTime,{.forwards=true,.maxSpeed=50},false);
//     //pros::delay(matchLoadTime);
//     chassis.setPose(chassis.getPose().x,14,chassis.getPose().theta);

    

//     //go score long goal
//     chassis.moveToPose(16,44,180,2000,{.forwards=false,.maxSpeed=110,.minSpeed=50,.earlyExitRange=5},true);
//     pros::delay(300);
//     matchLoad.set_value(false);
//     //intakeMotor.move_velocity(0); 
//     //outtakeMotor.move_velocity(0);
//     chassis.moveToPoint(17,100,1500,{.forwards=false,.maxSpeed=110,.minSpeed=60,.earlyExitRange=5},false);
//     chassis.setPose(distLeft.get()*0.0393701*cos(chassis.getPose().theta/180*3.1415926-3.1415926),chassis.getPose().y,chassis.getPose().theta);
//     chassis.moveToPose(23,110,-90,1500,{.forwards=false,.maxSpeed=110},false);
//     chassis.turnToPoint(19,80,1000,{.forwards=false,.maxSpeed=75},false);
//     chassis.moveToPoint(19,80,1500,{.forwards=false,.maxSpeed=110},true);

//     //chassis.moveToPose(28,50,0,1500,{.forwards=false,.maxSpeed=60},true);
//     scoreLong();

//     chassis.setPose(0,0,chassis.getPose().theta);

//     //long goal second time
//     matchLoad.set_value(true);
//     intakeMotor.move_voltage(12000);
//     outtakeMotor.move_velocity(-50);
//     chassis.moveToPoint(0,50,500,{.forwards=true,.maxSpeed=100},false);
//     chassis.moveToPoint(0,50,matchLoadTime,{.forwards=true,.maxSpeed=50},false);
//     //pros::delay(matchLoadTime);
    
//     chassis.moveToPoint(0,-5,1200,{.forwards=false,.maxSpeed=70},true);
//     pros::delay(300);
//     //intakeMotor.move_voltage(0);
//     //outtakeMotor.move_velocity(0);
//     scoreLong();
//     matchLoad.set_value(false);
//     chassis.setPose(0,0,chassis.getPose().theta);
    
//     //second park zone
//     //chassis.moveToPoint(18,36,500,{.forwards=true,.maxSpeed=90},false);
//     chassis.moveToPoint(18,36,1500,{.forwards=true,.maxSpeed=90},false);
//     //chassis.moveToPoint(25,36,1500,{.forwards=true,.maxSpeed=90},false);
//     chassis.turnToHeading(70,1000,{.maxSpeed=75},false);
//     intakeMotor.move_voltage(12000);
//     outtakeMotor.move_velocity(-50);
    
//     chassis.moveToPose(45,42,85,500,{.forwards=true,.maxSpeed=90},false);
//     pros::delay(400);
//     //matchLoad.set_value(true);
    
//     chassis.moveToPoint(105,42,3500,{.forwards=true,.maxSpeed=80},false);
//     pros::delay(500); 
//     intakeMotor.move_velocity(0);
//     outtakeMotor.move_velocity(0);
    
//     //matchLoad.set_value(false);

//     chassis.turnToHeading(0,1000,{.maxSpeed=75},false);
//     pros::delay(300);
//     chassis.setPose(0-distLeft.get()*0.0393701*cos(chassis.getPose().theta/180*3.1415926),0,chassis.getPose().theta);
//     //score right long
//     chassis.turnToPoint(-19,-20,500,{.forwards=false,.maxSpeed=75},true);
//     chassis.moveToPoint(-19,-20,1200,{.forwards=false,.maxSpeed=110},false);
//     chassis.turnToPoint(-19.5,-55,500,{.forwards=false,.maxSpeed=75},false);
//     chassis.moveToPoint(-19.5,-55,1200,{.forwards=false,.maxSpeed=110},false);
    
//     scoreLong();

//     chassis.setPose(0,0,chassis.getPose().theta);

//     //matchload
//     matchLoad.set_value(true);
//     intakeMotor.move_voltage(12000);
//     outtakeMotor.move_velocity(-50);
//     chassis.moveToPoint(0,50,500,{.forwards=true,.maxSpeed=100},false);
//     chassis.moveToPoint(0,50,matchLoadTime,{.forwards=true,.maxSpeed=50},false);
//     //pros::delay(matchLoadTime);
//     chassis.setPose(18-distLeft.get()*0.0393701*cos(chassis.getPose().theta/180*3.1415926),0,chassis.getPose().theta);

//     //high goal second
//     chassis.moveToPoint(chassis.getPose().x,5,300,{.forwards=false,.maxSpeed=90},true);
//     pros::delay(300);
//     //intakeMotor.move_voltage(0);
//     //outtakeMotor.move_velocity(0);
//     chassis.moveToPoint(-32,-44.5,1400,{.forwards=false,.maxSpeed=90},false);
//     chassis.moveToPoint(-38,-51.5,800,{.forwards=false,.maxSpeed=40},true);
//     pros::delay(400);
//     intakeMotor.move_velocity(-150);
//     outtakeMotor.move_velocity(-600);
//     pros::delay(300);
//     scoreSeven();

    
//     chassis.moveToPoint(-22,-35,2000,{.forwards=true,.maxSpeed=110},false);
//     chassis.turnToPoint(-16,-95,1000,{.forwards=false,.maxSpeed=75},false);
//     chassis.moveToPoint(-16,-100,1800,{.forwards=false,.maxSpeed=110,.minSpeed=60,.earlyExitRange=5},false);
//     chassis.turnToHeading(0,400,{.maxSpeed=75},false);
//     chassis.setPose(0-distLeft.get()*0.0393701*cos(chassis.getPose().theta/180*3.1415926),chassis.getPose().y,chassis.getPose().theta);
//     chassis.moveToPose(-16,-103,-90,1500,{.forwards=false,.minSpeed=50,.earlyExitRange=3},true);
//     chassis.turnToPoint(-16,-70,1000,{.forwards=false,.maxSpeed=75},false);
//     chassis.moveToPoint(-16,-70,1200,{.forwards=false,.maxSpeed=90},true);

//     scoreLong();
//     chassis.setPose(0,0,chassis.getPose().theta);

//     matchLoad.set_value(true);
//     intakeMotor.move_voltage(12000);
//     outtakeMotor.move_velocity(-50);
//     chassis.moveToPoint(0,-50,500,{.forwards=true,.maxSpeed=100},false);
//     chassis.moveToPoint(0,-50,matchLoadTime,{.forwards=true,.maxSpeed=50},false);
//     //pros::delay(matchLoadTime);
//     //intakeMotor.move_voltage(0);
//     //outtakeMotor.move_velocity(0);
//     chassis.moveToPoint(0,5,1500,{.forwards=false,.maxSpeed=70},true);
//     scoreLong();

//     chassis.setPose(0,0,chassis.getPose().theta);
//     matchLoad.set_value(false);
//     chassis.moveToPoint(-44,-5,2000,{.forwards=true,.maxSpeed=90},false);
//     chassis.turnToPoint(-45,-40,1000,{.maxSpeed=75},false);
//     chassis.moveToPoint(-45,-50,1500,{.forwards=true,.minSpeed=120},true);


// }


