#ifndef INSTRUCTIONPIPELINE_H
#define INSTRUCTIONPIPELINE_H

#include "Instruction.h"
#include "Scoreboard.h"
#include <iostream>

using namespace std;

class InstructionPipeline {
public:
	InstructionPipeline();
	~InstructionPipeline();

	bool cycle(Instruction instruction);
	void setScoreboard(Scoreboard *scoreboard);

private:
	Instruction reg_U0;
	Instruction reg_U1;
	Instruction reg_U2;

	Scoreboard *scoreboard_ptr;
};

#endif
