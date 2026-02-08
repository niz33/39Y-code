#pragma once
#include "main.h"

class Autonomous{
    public:
    static void print();
    static void test();

    static void matchLeftAutonBlue();
    static void matchRight2Goal();
    static void matchRight1Goal();
    static void matchLeft2Goal();
    static void matchLeft1Goal();
    static void matchRightCenter();
    static void matchLeftCenter();
    static void matchSolo();
    static void RightMidLong();
    
    static void skillsAuton1();
    static void skillsAuton2();
    static void skillsAuton3();

    
    


    private:
    const static double CLOCKWISE_CORRECTION;
    const static double COUNTERCLOCKWISE_CORRECTION;
    static double previous_heading;
    static double corrected_heading;
    
};
