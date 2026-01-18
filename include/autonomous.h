#pragma once
#include "main.h"

class Autonomous{
    public:
    static void initialize();
    static void debug();
    static void PIDtune();
    static void turnTo();
    static void moveTo();
    static void lateralPIDtune();
    static void correctHeading();
    static void matchForward();
    static void matchLeftAuton1();
    static void matchLeftAuton2();
    static void matchLeftAuton3();
    static void matchRightAuton2();
    static void matchSolo();
    static void test();
    static void skillsMove();
    static void skillsAuton();
    static void skillsAuton2();
    static void print();
    static void RightMidLong();


    private:
    const static double CLOCKWISE_CORRECTION;
    const static double COUNTERCLOCKWISE_CORRECTION;
    static double previous_heading;
    static double corrected_heading;
    
};
