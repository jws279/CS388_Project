#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "Instruction.h"

class Scoreboard7600 {
private:

    FunctionalUnit floatingAdder;
    FunctionalUnit multiplier;
    FunctionalUnit divider;
    FunctionalUnit fixedAdder;
    FunctionalUnit increment;
    FunctionalUnit boolean;
    FunctionalUnit shift;
    FunctionalUnit popCount;
    FunctionalUnit normalize;

    void clockTick();

public:
    bool receiveNextInstruction(Instruction instruction);
    Scoreboard7600();
}

#endif
