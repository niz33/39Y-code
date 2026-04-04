#pragma once
#include "main.h"
#include <queue>

class Control{
    public:
        static void drive();

        static void intake();

        enum IntakeState{
            longGoal,
            highGoal,
            lowGoal,
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

        static int storageTime;

    public:
        static bool load;
        static bool descoring;
        static bool middleDescoring;

        static bool lastR2;
        static bool lastA;
        static bool lastB;

        
        static void update();
        static void initialize();
};
