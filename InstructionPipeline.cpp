#include "InstructionPipeline.h"

InstructionPipeline::InstructionPipeline(Scoreboard7600 *scoreboard) {
	reg_U0 = 0;
	reg_U1 = 0;
	reg_U2 = 0;

	scoreboard_ptr = scoreboard;
}

InstructionPipeline::~InstructionPipeline() {
	// Do nothing
}

bool InstructionPipeline::cycle(Instruction* instruction) {
	if(scoreboard_ptr->receiveNextInstruction(*reg_U2)) {
		reg_U2 = reg_U1;
		reg_U1 = reg_U0;
		reg_U0 = instruction;

		return true;
	}
	else {
		return false;
	}
	return false;
}
