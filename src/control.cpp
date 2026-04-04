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
Control::IntakeState Control::intakeState = Control::non;
Control::ScoringColor Control::scoringColor = Control::red;
Control::ColorSortingType Control::colorSortingType = Control::none;
double Control::IntakeTorque = 0;
double Control::OuttakeTorque = 0;
double Control::SortTorque = 0;
double Control::MidTorque = 0;
int Control::storageTime=0;

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
     else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {

        
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
        intakeState=storage;
    } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
        intakeState=lowGoal;
    } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
        intakeMotor.move_velocity(300);
        outtakeMotor.move_velocity(300);
        Control::cooldown=0;
    } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
        intakeMotor.move_velocity(-300);
        outtakeMotor.move_velocity(-600);
        Control::cooldown=0;
    } else {
        intakeState=non;
        Control::cooldown=0;
    }

    


    if(cRight.size()>=cDelay){
        cRight.pop();
    }

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

    intake();
}


void Control::initialize(){
    intakeMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
    outtakeMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
    leftWheels.set_brake_mode_all(MOTOR_BRAKE_COAST);
    rightWheels.set_brake_mode_all(MOTOR_BRAKE_COAST);
}





void Control::update(){
    Control::drive();
    // Control::grabber();
    // Control::wallStake();
}

void Control::intake(){

    

    if(intakeState==longGoal){
        intakeMotor.move_voltage(12000);
        midMotor.move_voltage(12000);
        sortMotor.move_voltage(12000);
        outtakeMotor.move_voltage(12000);
    }
    if(intakeState==highGoal){
        intakeMotor.move_voltage(12000);
        midMotor.move_voltage(12000);
        sortMotor.move_voltage(-12000);
        outtakeMotor.move_velocity(100);
    }
    if(intakeState==lowGoal){
        intakeMotor.move_voltage(-12000);
        midMotor.move_voltage(-12000);
        sortMotor.move_velocity(-60);
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

        intakeMotor.move_voltage(12000);
        //midMotor.move_voltage(12000);
        // sortMotor.move_voltage(12000);
        // outtakeMotor.move_voltage(12000);
        
        // intakeMotor.move_voltage(12000);
        midMotor.move_velocity(70);
        outtakeMotor.move_voltage(1000);
        sortMotor.move_voltage(800);


        if(cSensor.get_hue()>80){
            if(SortTorque<0.15){
                outtakeMotor.move_velocity(40);
            }
        }

        if(cSensor2.get_hue()<20){
            if(SortTorque<0.15){
                midMotor.move_voltage(10000);
                outtakeMotor.move_velocity(-50);
            }
            else{
                midMotor.move_voltage(10000);
            }
            
        }

        if(SortTorque>0.15){
            midMotor.move_voltage(2000);
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
    }

    if(intakeState==non){
        intakeMotor.move_voltage(0);
        midMotor.move_voltage(0);
        sortMotor.move_voltage(0);
        outtakeMotor.move_voltage(0);
    }

}