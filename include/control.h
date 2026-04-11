#pragma once
#include "main.h"
#include <queue>

class Control{
    public:
        static void drive();

        static void intake();

        static void intakeLoop();

        static void motorUpdate();

        enum IntakeState{
            longGoal,
            highGoal,
            highGoalSlow,
            lowGoal,
            lowGoalCooling,
            storage,
            non,
        };

        enum ScoringColor{
            red,
            blue,
        };

        enum ColorSortingType{
            stop,
            sort,
            none,
        };
        
        static IntakeState intakeState;
        static ScoringColor scoringColor;
        static ColorSortingType colorSortingType;



        static int cDelay;
        static std::queue<int> cRight;
        static int countdown;
        static int cooldown;
        static int middleDescoreDuration;

        static double IntakeTorque;
        static double OuttakeTorque;
        static double SortTorque;
        static double MidTorque;
        static double SortVelocity;

        static int storageTime;
        static int highGoalTime;
        static int lowGoalCooldown;

        static double outtakeTargetVelocity;
        static double outtakeIntegral;

        static double midMotorTargetVelocity;
        static double midMotorIntegral;



        static bool lastR2;
        static bool lastA;
        static bool lastB;
        static bool lastDown;
        static bool lastY;


        static bool wingRState;
        static bool feetState;
        static bool hoodState;
        static bool matchLoadState;



        
        static void update();
        static void initialize();
};
