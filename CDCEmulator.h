#ifndef CDCEMULATOR_H
#define CDCEMULATOR_H

#include <vector>
#include "Scoreboard7600.h"
#include "InstructionPipeline.h"
#include "InstructionParser.h"
#include "TimingDiagram.h"

class CDCEmulator {
public:
	CDCEmulator();
	~CDCEmulator();
	virtual int run();
	TimingDiagram *timingDiagram;

private:

protected:
	int fetchDelay;
	Scoreboard7600 *scoreboard;
	InstructionPipeline *instrPipe;

};

#endif
