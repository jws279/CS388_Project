#ifndef CDCEMULATOR_H
#define CDCEMULATOR_H

#include <vector>
#include <string>
#include "InstructionPipeline.h"
#include "InstructionParser.h"
#include "TimingDiagram.h"

class CDCEmulator {
public:
	CDCEmulator();
	~CDCEmulator();

	// Virtual run function to be overwritten by child classes
	virtual int run(string infile, string outfile);

	// Pointer to class that builds the final timing diagram
	TimingDiagram *timingDiagram;

private:

protected:
	// Delay associated with fetch and store instructions
	int fetchDelay;

	// Pointer to instruction pipeline
	InstructionPipeline *instrPipe;

};

#endif
