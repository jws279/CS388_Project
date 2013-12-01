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

    FunctionalUnit functionalUnits[] = {floatingAdder, multiplier, divider, fixedAdder, increment, boolean, shift, popCount, normalize};

    void clockTick();
    bool functionalUnitConflict(FunctionalUnit fu);
    bool writeAfterWriteConflict(Instruction inst);
    bool readAfterWriteConflict(Instruction inst);
    bool writeAfterReadConflict(Instruction inst);
    bool instIsLong(Instruction inst);

public:
    Scoreboard7600();
    bool receiveNextInstruction(Instruction instruction);
}

#endif


////////MAYBE SHOULD MAKE THIS SCOREBOARD WHICH 7600 AND 6600 INHERITS
