#ifndef CDCEMULATOR_H
#define CDCEMULATOR_H

#include <vector>
#include <string>
#include "Scoreboard7600.h"
#include "InstructionPipeline.h"
#include "InstructionParser.h"
#include "TimingDiagram.h"

class CDCEmulator {
public:
	CDCEmulator();
	~CDCEmulator();
	virtual int run(string infile, string outfile);

	TimingDiagram *timingDiagram;

private:

protected:
	int fetchDelay;
	InstructionPipeline *instrPipe;

};

#endif
