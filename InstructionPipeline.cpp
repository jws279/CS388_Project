#include "InstructionPipeline.h"

InstructionPipeline::InstructionPipeline(Scoreboard7600 *scoreboard) {

	scoreboard_ptr = scoreboard;
	reg_U2.setNoop();
	reg_U1.setNoop();
	reg_U0.setNoop();
}

InstructionPipeline::~InstructionPipeline() {
	// Do nothing
}

bool InstructionPipeline::cycle(Instruction instruction) {
	cout<<reg_U2.getFm()<<" "<<reg_U2.getI()<<" "<<reg_U2.getJ()<<" "<<reg_U2.getK()<<endl;
/*	if(!reg_U2.isValid()) {
		reg_U2 = reg_U1;
		reg_U1 = reg_U0;
		reg_U0 = instruction;
	}
	else */if(scoreboard_ptr->receiveNextInstruction(reg_U2)) {
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
