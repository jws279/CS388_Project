#ifndef SCOREBOARD_7600_H
#define SCOREBOARD_7600_H

#include "Instruction.h"
#include "FunctionalUnit.h"
#include "TimingDiagram.h"
#include "Scoreboard.h"
#include <iostream>

using namespace std;

class Scoreboard7600 : public Scoreboard  {
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
    virtual bool receiveNextInstruction(Instruction instruction);
    virtual bool stopFound();
	virtual void cycleTillDone();
    virtual void flushPipelines();

	TimingDiagram *timingDiagram;
};

#endif
