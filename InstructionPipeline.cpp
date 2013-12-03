#include "InstructionPipeline.h"

InstructionPipeline::InstructionPipeline() {
	reg_U2.setNoop();
	reg_U1.setNoop();
	reg_U0.setNoop();

	reg_U2.setInstructionNumb(0);
	reg_U1.setInstructionNumb(0);
	reg_U0.setInstructionNumb(0);
	
}

InstructionPipeline::~InstructionPipeline() {
	// Do nothing
}

bool InstructionPipeline::cycle(Instruction instruction) {
	if(scoreboard_ptr->receiveNextInstruction(reg_U2)) {
		reg_U2 = reg_U1;
		reg_U1 = reg_U0;
		reg_U0 = instruction;

		if(!reg_U2.isValid()) {
			reg_U2.setNoop();
		}

		return true;
	}
	else {
		return false;
	}
	return false;
}

void InstructionPipeline::setScoreboard(Scoreboard *scoreboard) {
	scoreboard_ptr = scoreboard;
}

void InstructionPipeline::clearPipeline() {
	reg_U2.setNoop();
	reg_U1.setNoop();
	reg_U0.setNoop();

	reg_U2.setInstructionNumb(0);
	reg_U1.setInstructionNumb(0);
	reg_U0.setInstructionNumb(0);
}
