#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "Instruction.h"
#include "FunctionalUnit.h"
#include "TimingDiagram.h"
#include <iostream>

using namespace std;

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

    bool stop_found;

    void clockTick();
    bool functionalUnitConflict(FunctionalUnit *fu);
    bool writeAfterWriteConflict(Instruction inst);
    bool readAfterWriteConflict(Instruction inst);
    bool writeAfterReadConflict(Instruction inst);

public:
    Scoreboard7600(TimingDiagram *timingDiagram);
	~Scoreboard7600();
    bool receiveNextInstruction(Instruction instruction);
    bool stopFound();
	void cycleTillDone();

	TimingDiagram *timingDiagram;
};

#endif
