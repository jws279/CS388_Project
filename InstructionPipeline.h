#ifndef INSTRUCTIONPIPELINE_H
#define INSTRUCTIONPIPELINE_H

#include "Instruction.h"
#include "Scoreboard7600.h"

class InstructionPipeline {
public:
	InstructionPipeline(Scoreboard7600 *scoreboard);
	~InstructionPipeline();

	bool cycle(Instruction* instruction);

private:
	Instruction *reg_U0;
	Instruction *reg_U1;
	Instruction *reg_U2;

	Scoreboard7600 *scoreboard_ptr;
};

#endif