#ifndef SCOREBOARD_6600_H
#define SCOREBOARD_6600_H

#include "Instruction.h"
#include "FunctionalUnit.h"
#include "TimingDiagram.h"
#include <iostream>

using namespace std;

class Scoreboard6600 {
private:

    FunctionalUnit *floatingAdder;
    FunctionalUnit *multiplier1;
    FunctionalUnit *multiplier2;
    FunctionalUnit *divider;
    FunctionalUnit *fixedAdder;
    FunctionalUnit *incrementer1;
    FunctionalUnit *incrementer2;
    FunctionalUnit *booleaner;
    FunctionalUnit *shifter;
    FunctionalUnit *brancher;

    FunctionalUnit** functionalUnits;
    static const int num_FU = 10;

    bool stop_found;

    void clockTick();
    bool functionalUnitConflict(FunctionalUnit *fu);
    bool writeAfterWriteConflict(Instruction inst);
    bool readAfterWriteConflict(Instruction inst);
    bool writeAfterReadConflict(Instruction inst);

public:
    Scoreboard6600(TimingDiagram *timingDiagram);
    ~Scoreboard6600();
    bool receiveNextInstruction(Instruction instruction);
    bool stopFound();
    void cycleTillDone();
    void flushPipelines();

    TimingDiagram *timingDiagram;
};

#endif
