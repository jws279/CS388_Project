#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "Instruction.h"
#include "FunctionalUnit.h"
#include "TimingDiagram.h"
#include <iostream>

using namespace std;

class Scoreboard {
private:

public:
    virtual bool receiveNextInstruction(Instruction instruction) = 0;
	virtual bool stopFound() = 0;
	virtual void cycleTillDone() = 0;
    virtual void flushPipelines() = 0;

};

#endif
