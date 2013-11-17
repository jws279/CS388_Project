#ifndef CDCEMULATOR_H
#define CDCEMULATOR_H

#include <vector>
#include "scoreboard.h"

class CDCEmulator {
public:
	CDCEmulator();
	~CDCEmulator();
	virtual int run();

private:
	//Vector<Instruction_t> instructionStack; //Not actually instructions, need to be 60-bit words
	//Registers
	//InstructionPipeline
	Scoreboard scoreboard;
	//ALU/Functional Units
	//CentralStorage

	//TableBuilder

};

#endif