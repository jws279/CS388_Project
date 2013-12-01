#ifndef CDCEMULATOR_H
#define CDCEMULATOR_H

#include <vector>
#include "Scoreboard7600.h"
#include "InstructionPipeline.h"
#include "InstructionParser.h"

class CDCEmulator {
public:
	CDCEmulator();
	~CDCEmulator();
	virtual int run();

private:
	//Vector<Instruction_t> instructionStack; //Not actually instructions, need to be 60-bit words
	//TableBuilder

protected:
	int fetchDelay;
	Scoreboard7600 *scoreboard;
	InstructionPipeline *instrPipe;

};

#endif
