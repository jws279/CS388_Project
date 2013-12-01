#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "Instruction.h"
#include "FunctionalUnit.h"


class Scoreboard7600 {
private:

    FunctionalUnit *floatingAdder;
    FunctionalUnit *multiplier;
    FunctionalUnit *divider;
    FunctionalUnit *fixedAdder;
    FunctionalUnit *incrementer;
    FunctionalUnit *booleaner;
    FunctionalUnit *shifter;
    FunctionalUnit *popCounter;
    FunctionalUnit *normalizer;

    FunctionalUnit** functionalUnits;
	static const int num_FU = 9;

    void clockTick();
    bool functionalUnitConflict(FunctionalUnit *fu);
    bool writeAfterWriteConflict(Instruction inst);
    bool readAfterWriteConflict(Instruction inst);
    bool writeAfterReadConflict(Instruction inst);
    bool instIsLong(Instruction inst);

public:
    Scoreboard7600();
	~Scoreboard7600();
    bool receiveNextInstruction(Instruction instruction);
};

#endif


////////MAYBE SHOULD MAKE THIS SCOREBOARD WHICH 7600 AND 6600 INHERITS
