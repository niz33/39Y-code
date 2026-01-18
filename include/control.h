#pragma once
#include "main.h"
#include <queue>

class Control{
    private:
        static void driveCodeTank();
        static void driveCodeArcade();
        static void intake();
        static void park();
        static void wallStake();

        
        

        static int cDelay;
        static std::queue<int> cRight;
        static int countdown;
        static int cooldown;

    public:
        static double hang_speed;
        static bool parking;
        static bool load;
        static bool descoring;

        
        static bool grabberState;
        static void update();
        static void initialize();
        static void intakeVelocity(int v);
};
