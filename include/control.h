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
        static int middleDescoreDuration;

    public:
        static bool load;
        static bool descoring;
        static bool middleDescoring;

        static bool lastR2;
        static bool lastA;
        static bool lastB;

        
        static void update();
        static void initialize();
        static void intakeVelocity(int v);
};
