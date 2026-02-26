#include "main.h"


bool Control::descoring = false;
bool Control::load = false;
bool Control::middleDescoring = false;
bool Control::lastR2 = false;
bool Control::lastA = false;
bool Control::lastB = false;
int Control::cDelay = 3;
int Control::countdown = 0;
int Control::cooldown = 0;
int Control::middleDescoreDuration = 0;

std::queue<int> Control::cRight;
void Control::driveCodeArcade(){

    // double forward = Utilities::drive_control_map(master.get_analog(ANALOG_LEFT_Y));
    // if(abs(forward)<0.1) forward=0;

    // double turn = Utilities::drive_control_map(master.get_analog(ANALOG_RIGHT_X));
    // if(abs(turn)<0.1) turn=0;
    // double left=forward*500+turn*(300+forward*100);
    // double right=forward*500-turn*(300+forward*100);
    // if(left>600){
    //     int df=left-600;
    //     left=600;
    //     right-=df;
    // }
    // if(left<-600){
    //     int df=left+600;
    //     left=-600;
    //     right-=df;
    // }
    // if(right>600){
    //     int df=right-600;
    //     right=600;
    //     left-=df;
    // }
    // if(right<-600){
    //     int df=right+600;
    //     right=-600;
    //     left-=df;
    // }

    // DriveTrain::move_velocity(Utilities::bound_by(-600,600,left),Utilities::bound_by(-600,600,right));
    
    // if(turn==0&&forward==0){
    //     //DriveTrain::stopLeft();
    //     //DriveTrain::stopRight();
    // }


    // get left y and right x positions
    int leftY = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int leftX = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    // move the robot
    // prioritize steering slightly
    chassis.arcade(0-leftY, leftX, false, 0.75);
}

void Control::driveCodeTank(){
    double left = Utilities::drive_control_map(master.get_analog(ANALOG_LEFT_Y));
    double right = Utilities::drive_control_map(master.get_analog(ANALOG_RIGHT_Y));

    // if(left==0){
    //     DriveTrain::stopLeft();
    // }
    // if(right==0){
    //     DriveTrain::stopRight();
    // }
    DriveTrain::move_velocity(left*600,right*600);
}

void Control::intake(){
    int temp=1;
    if (cSensor.get_hue()<35) temp=0;
    cRight.push(temp);

    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        intakeMotor.move_voltage(12000);
        outtakeMotor.move_voltage(12000);
        Control::cooldown=0;

    } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {

        
        Control::cooldown++;
        if(cooldown>20){
            intakeMotor.move_velocity(600);
            outtakeMotor.move_velocity(-100);
        }
        else{
            //intakeMotor.move_voltage(-12000);
            intakeMotor.move_velocity(-100);
            outtakeMotor.move_voltage(-12000);
        }


        intakeMotor.move_velocity(400);
        outtakeMotor.move_velocity(-50);


    }
     else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {

        
        Control::cooldown++;
        if(cooldown>20){
            intakeMotor.move_velocity(600);
            outtakeMotor.move_velocity(-100);
        }
        else{
            //intakeMotor.move_voltage(-12000);
            intakeMotor.move_velocity(-100);
            outtakeMotor.move_voltage(-12000);
        }


        intakeMotor.move_velocity(300);
        outtakeMotor.move_velocity(-50);


    } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        intakeMotor.move_voltage(12000);
        outtakeMotor.move_velocity(-50);
       
        Control::cooldown=0;
    } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
        intakeMotor.move_voltage(-12000);
        outtakeMotor.move_voltage(-12000);
        Control::middleDescoreDuration++;
        Control::cooldown=0;
    } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
        intakeMotor.move_velocity(300);
        outtakeMotor.move_velocity(300);
        Control::cooldown=0;
    } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
        intakeMotor.move_velocity(-300);
        outtakeMotor.move_velocity(-600);
        Control::cooldown=0;
    } else {
        intakeMotor.move_velocity(30);
        outtakeMotor.move_velocity(0);
        Control::cooldown=0;
    }

    


    if(cRight.size()>=cDelay){
        cRight.pop();
    }
}


void Control::initialize(){
    intakeMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
    outtakeMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
    leftWheels.set_brake_mode_all(MOTOR_BRAKE_COAST);
    rightWheels.set_brake_mode_all(MOTOR_BRAKE_COAST);
}

void Control::park(){
    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_A)){
        // if(Control::middleDescoreDuration>0&&Control::middleDescoreDuration<15){
        //     Control::middleDescoring=!Control::middleDescoring;
        //     middleDescore.set_value(Control::middleDescoring);
        // }
        // Control::middleDescoreDuration=0;
        if(Control::lastA==false){
            Control::middleDescoring=!Control::middleDescoring;
            middleDescore.set_value(Control::middleDescoring);
        }
        Control::lastA=true;
    }
    else{
        Control::lastA=false;
    }
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)){
        if(Control::lastB==false){
            Control::load=1-Control::load;
            matchLoad.set_value(load);
        }
        Control::lastB=true;
			
	}
    else{
        Control::lastB=false;
    }
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)){
        if(Control::lastR2==false){
            Control::descoring=1-Control::descoring;
            wing.set_value(Control::descoring);
        }
        Control::lastR2=true;
	}
    else{
        Control::lastR2=false;
    }
}



void Control::update(){
    Control::driveCodeArcade();
    Control::intake();
    Control::park();
    // Control::grabber();
    // Control::wallStake();
}