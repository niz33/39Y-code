#include "control.h"
#include "globals.h"
#include "main.h"



bool Control::lastR2 = false;
bool Control::lastA = false;
bool Control::lastB = false;
bool Control::lastDown = false;
bool Control::lastY = false;
bool Control::wingRState = false;
bool Control::wingLState = false;
bool Control::feetState = false;
bool Control::hoodState = false;  
bool Control::roofState = false;
bool Control::matchLoadState = false;
bool Control::middleGoalDescoreState = false;
int Control::cDelay = 13;
int Control::countdown = 0;
int Control::cooldown = 0;
int Control::middleDescoreDuration = 0;
Control::IntakeState Control::intakeState = Control::non;
Control::IntakeState Control::previousState = Control::non;
Control::ScoringColor Control::scoringColor = Control::blue;
Control::ColorSortingType Control::colorSortingType = Control::none;
double Control::IntakeTorque = 0;
double Control::OuttakeTorque = 0;
double Control::SortTorque = 0;
double Control::MidTorque = 0;
double Control::SortVelocity = 0;
int Control::storageTime=0;
int Control::highGoalTime=0;
int Control::lowGoalCooldown=0;
std::queue<int> Control::colorHistoryLong;
std::queue<int> Control::colorHistoryMid;

double Control::outtakeTargetVelocity=0;
double Control::outtakeIntegral=0;
double Control::midMotorTargetVelocity=0;
double Control::midMotorIntegral=0;

int Control::blockcount = 0;

float Control:: targetAngle = sortMotor.get_position();

float Control:: targetOuttakeAngle = outtakeMotor.get_position();

bool prevDetected = false;

std::queue<int> Control::cRight;
void Control::drive(){


    // get left y and right x positions
    int leftY = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int leftX = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    // move the robot
    // prioritize steering slightly
    chassis.arcade(leftY, leftX, false, 0.75);

    int temp=1;
    if (cSensor.get_hue()<35) temp=0;
    cRight.push(temp);

    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        intakeState=longGoal;

    } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {

        
        intakeState=highGoal;


    }
     else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        intakeState=storage;
    } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
        intakeState=lowGoal;
    } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)&&distFront.get()<150){
        //Autonomous::matchDescoreReverse();
        chassis.cancelAllMotions();
        Autonomous::matchDescore();
        intakeState=storage;

    } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)&&distFront.get()<150){
        chassis.cancelAllMotions();
        Autonomous::matchDescoreReverse();
        intakeState=storage;

    } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
        // intakeMotor.move_velocity(-300);
        // outtakeMotor.move_velocity(-600);
        Control::cooldown=0;
    } else {
        intakeState=non;
        Control::cooldown=0;
    }

    


    if(cRight.size()>=cDelay){
        cRight.pop();
    }




    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)){
        //if(!hoodState){
            matchLoadState=!matchLoadState;
            matchLoad.set_value(matchLoadState);
        //}
        
	}

    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)){
        wingRState=!wingRState;
        wingR.set_value(wingRState);
	}

    
   

    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)){
        feetState=!feetState;
        feet.set_value(feetState);
    }

    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)){
        roofState=!roofState;
        //matchLoadState=false;
        //matchLoad.set_value(false);
        //pros::delay(300);
        roof.set_value(roofState);
    }
    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)){
        hoodState=!hoodState;
        hood.set_value(hoodState);
        
    }

     if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)){
        middleGoalDescoreState =!middleGoalDescoreState;
        middleDescore.set_value(middleGoalDescoreState);
    }
}

void Control::intakeLoop(){
    while(true){
        Control::intake();
        //Control::motorUpdate();
        Control::anglePID();
        pros::delay(10);
    }
}


void Control::initialize(){
    intakeMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
    outtakeMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
    leftWheels.set_brake_mode_all(MOTOR_BRAKE_COAST);
    rightWheels.set_brake_mode_all(MOTOR_BRAKE_COAST);
}





void Control::update(){
    Control::drive();
    Control::intake();
    Control::anglePID();
    //Control::motorUpdate();
}

void Control::intake(){/*

    if(lowGoalCooldown>0&&intakeState!=lowGoal){
        lowGoalCooldown--;
        intakeState=lowGoalCooling;
        sortMotor.move_voltage(200);
    }

    

    if(intakeState==longGoal){
        intakeMotor.move_voltage(12000);
        midMotor.move_voltage(12000);
        sortMotor.move_voltage(12000);
        outtakeMotor.move_voltage(12000);
        hood.set_value(true);
    }else{
        hood.set_value(false);
    }
    if(intakeState==highGoal||intakeState==highGoalSlow){
        highGoalTime++;
        sortMotor.move_voltage(-12000);
        if(highGoalTime<20&&dSensor.get()<70){
            outtakeTargetVelocity=30;
            if(highGoalTime<10){
                intakeMotor.move_voltage(0);
                midMotor.move_voltage(0);
            } 
        }
        else{
            intakeMotor.move_voltage(12000);
            midMotor.move_voltage(12000);
            outtakeMotor.move_velocity(1000);
            outtakeTargetVelocity=1000;
            if(intakeState==highGoalSlow){
                intakeMotor.move_voltage(12000);
                midMotor.move_voltage(12000);
                outtakeMotor.move_velocity(1000);
                sortMotor.move_velocity(-20);
            }
        }
        
        
        
    }else{
        highGoalTime=0;
        
    }
    if(intakeState==lowGoal){
        lowGoalCooldown=5;
        intakeMotor.move_voltage(-12000);
        midMotor.move_voltage(-12000);
        sortMotor.move_voltage(-12000);
        outtakeMotor.move_voltage(-12000);
    }
    if(intakeState==storage){
        storageTime++;
        if(storageTime>10){
            IntakeTorque*=0.8;
            IntakeTorque+=0.2*intakeMotor.get_torque();
            OuttakeTorque*=0.8;
            OuttakeTorque+=0.2*outtakeMotor.get_torque();
            SortTorque*=0.8;
            SortTorque+=0.2*sortMotor.get_torque();
            MidTorque*=0.8;
            MidTorque+=0.2*midMotor.get_torque();
        }
        if(storageTime>40){
            SortVelocity*=0.8;
            SortVelocity+=0.2*sortMotor.get_actual_velocity();
        }

        intakeMotor.move_voltage(12000);
        midMotor.move_voltage(4500);
        // sortMotor.move_voltage(12000);
        // outtakeMotor.move_voltage(12000);
        
        // intakeMotor.move_voltage(12000);
        midMotorTargetVelocity=1000;
        outtakeMotor.move_voltage(0);
        sortMotor.move_voltage(400);
        outtakeTargetVelocity=1000;


        if(cSensor.get_hue()>80||cSensor.get_hue()<20){
            if(dSensor.get()>70){
                outtakeTargetVelocity=80;
                //midMotor.move_voltage(3500);
                //sortMotor.move_voltage(800);
            }
        }

        // if(cSensor2.get_hue()<20){
        //     if(SortVelocity>3){
        //         midMotor.move_voltage(10000);
        //         outtakeMotor.move_velocity(-50);
        //     }
        //     else{
        //         midMotor.move_voltage(10000);
        //     }
            
        // }

        if(dSensor.get()<70){
            midMotorTargetVelocity=1000;
            midMotor.move_voltage(3000);
            sortMotor.move_voltage(1000);
            outtakeMotor.move_voltage(1000);
            //outtakeMotor.move_voltage(800);
        }

        // if(SortTorque>0.15){
        //     sortMotor.move_voltage(2000);
        //     if(OuttakeTorque>0.145){
        //         outtakeMotor.move_voltage(1000);
        //         if(MidTorque>0.2){
        //             outtakeMotor.move_voltage(500);
        //             midMotor.move_voltage(4500);
        //             if(MidTorque>0.4){
        //                 midMotor.move_voltage(700);
        //             }
        //         }
        //     }
        // }

    }else{
        storageTime=0;
        outtakeTargetVelocity=1000;
        midMotorTargetVelocity=1000;
    }

    if(intakeState==non){
        intakeMotor.move_voltage(0);
        midMotor.move_voltage(0);
        sortMotor.move_voltage(0);
        outtakeMotor.move_voltage(0);
    }

    int distance = intakeSensor.get_distance();

    bool detected = (distance < 30);

    if (detected && !prevDetected){
        blockcount++;
    }

    prevDetected = detected;

    
    */

    if(intakeState==longGoal){
        int flag=0;
        if(scoringColor==ScoringColor::red&&cSensor2.get_hue()>60) flag=1;
        if(scoringColor==ScoringColor::blue&&cSensor2.get_hue()<30) flag=1;
        colorHistoryLong.push(flag);
        if(colorHistoryLong.front()==1){
            intakeMotor.move_voltage(12000);
            midMotor.move_voltage(12000);
            sortMotor.move_voltage(12000);
            outtakeMotor.move_voltage(-12000);
        }
        else{
            intakeMotor.move_voltage(12000);
            midMotor.move_voltage(12000);
            sortMotor.move_voltage(12000);
            outtakeMotor.move_voltage(12000);
        }
        //scoringColor=Control::blue;
        if(colorHistoryLong.size()>cDelay) colorHistoryLong.pop();
        
        hood.set_value(true);
        previousState = longGoal;


    }else{
        hood.set_value(false);
        //clear queue
        colorHistoryLong = std::queue<int>();
    }
    if(intakeState==lowGoal){
        intakeMotor.move_voltage(-12000);
        midMotor.move_voltage(-12000);
        sortMotor.move_voltage(-12000);
        outtakeMotor.move_voltage(-12000);
        previousState = lowGoal;
    }

    if(intakeState==lowGoalSlow){
        intakeMotor.move_velocity(-300);
        midMotor.move_voltage(-12000);
        sortMotor.move_voltage(-12000);
        outtakeMotor.move_voltage(-12000);
        previousState = lowGoalSlow;
    }

    
    if(intakeState==storage){
        if(previousState != storage){
            blockcount = 0;
            intakeMotor.move_voltage(12000);
            sortMotor.move_voltage(-12000);
            outtakeMotor.move_voltage(-12000);
            pros::delay(200);
            intakeMotor.move_voltage(0);
            sortMotor.move_voltage(0);
            outtakeMotor.move_voltage(0);

            
        }
        
        int distance = intakeSensor.get_distance();
        float stepAngle = 105;
        float stepAngleOuttake = 60;

        bool detected = (distance < 30);

        if(dSensor.get_distance() < 50){
            blockcount = 4;
        }
        if(intakeSensor.get_distance() < 30 && dSensor.get_distance() < 50){
            blockcount = 5;
        }


        if (detected && !prevDetected){
        blockcount++;
            if(blockcount < 5){
            targetAngle = sortMotor.get_position() + stepAngle;
            targetOuttakeAngle = outtakeMotor.get_position() + stepAngleOuttake;
            }
        }

        prevDetected = detected;



    intakeMotor.move_voltage (12000);


    previousState = storage;

    }

    if(intakeState == highGoal){
        if (previousState != highGoal) {
        
        
        outtakeMotor.move_voltage(12000);
        pros::delay(50);
        intakeMotor.move_voltage(-12000);
        sortMotor.move_voltage(-12000);
        outtakeMotor.move_voltage(-12000);
        pros::delay(150);
        intakeMotor.move_voltage(0);
        sortMotor.move_voltage(0);
        outtakeMotor.move_voltage(0);
        }

        int flag=0;
        if(scoringColor==ScoringColor::red&&cSensor2.get_hue()>60) flag=1;
        if(scoringColor==ScoringColor::blue&&cSensor2.get_hue()<30) flag=1;
        colorHistoryMid.push(flag);
        if(colorHistoryMid.front()==1){
            intakeMotor.move_voltage(12000);
            sortMotor.move_voltage(12000);
            outtakeMotor.move_voltage(-12000);
        }
        else{
            intakeMotor.move_voltage(12000);
            sortMotor.move_voltage(12000);
            outtakeMotor.move_voltage(-12000);
        }
        //scoringColor=Control::blue;
        if(colorHistoryMid.size()>cDelay-5) colorHistoryMid.pop();

        
        previousState = highGoal;


    
    }else{
        colorHistoryMid = std::queue<int>();
    }
    if(intakeState == highGoalSlow){
        if (previousState != highGoalSlow){
        outtakeMotor.move_voltage(12000);
        pros::delay(50);
        intakeMotor.move_voltage(-12000);
        sortMotor.move_voltage(-12000);
        outtakeMotor.move_voltage(-12000);
        pros::delay(150);
        intakeMotor.move_voltage(0);
        sortMotor.move_voltage(0);
        outtakeMotor.move_voltage(0);
        }
        intakeMotor.move_voltage(5000);
        sortMotor.move_voltage(5000);
        outtakeMotor.move_voltage(-2000);
        previousState = highGoalSlow;


    }
   

    if(intakeState==non){
        intakeMotor.move_voltage(0);
        midMotor.move_voltage(0);
        sortMotor.move_voltage(0);
        outtakeMotor.move_voltage(0);
        //previousState = non;
    }
}

void Control::anglePID() {
    
    if (intakeState != storage) return;

    sortMotor.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
    sortMotor.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);

    outtakeMotor.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
    outtakeMotor.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);

   
    static float prevErrorSort = 0;

    float kP_sort = 150;
    float kD_sort = 15;

    float sortAngle = sortMotor.get_position();
    float sortError = targetAngle - sortAngle;
    float sortDerivative = sortError - prevErrorSort;

    float sortPower = kP_sort * sortError + kD_sort * sortDerivative;

    if (sortPower > 12000) sortPower = 12000;
    if (sortPower < -12000) sortPower = -12000;

    if (fabs(sortError) < 2) {
        sortPower = 0;
    }

    sortMotor.move_voltage(sortPower);
    prevErrorSort = sortError;

    static float prevErrorOut = 0;

    float kP_out = 140;
    float kD_out = 12;

    float outAngle = outtakeMotor.get_position();
    float outError = targetOuttakeAngle - outAngle;
    float outDerivative = outError - prevErrorOut;

    float outPower = kP_out * outError + kD_out * outDerivative;

    if (outPower > 12000) outPower = 12000;
    if (outPower < -12000) outPower = -12000;

    if (fabs(outError) < 2|| dSensor.get_distance() < 50) {
        outPower = 0;
    }

    outtakeMotor.move_voltage(outPower);
    prevErrorOut = outError;
}



/*
void Control::motorUpdate(){
    if(outtakeTargetVelocity!=1000){
        double v=outtakeMotor.get_actual_velocity();
        double error=outtakeTargetVelocity-v;
        double kP=50, kI=1;
        outtakeIntegral+=error;
        double output=kP*error+kI*outtakeIntegral;
        outtakeMotor.move_voltage(output);
    }

    if(midMotorTargetVelocity!=1000){
        double v=midMotor.get_actual_velocity();
        double error=midMotorTargetVelocity-v;
        double kP=50, kI=1;
        midMotorIntegral+=error;
        double output=kP*error+kI*midMotorIntegral;
        midMotor.move_voltage(output);
    }
}*/