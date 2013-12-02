#include "CDC7600Emulator.h"

CDC7600Emulator::CDC7600Emulator() {
	fetchDelay = 4;
}

CDC7600Emulator::~CDC7600Emulator() {
	
}

int CDC7600Emulator::run() {
	vector<Instruction> instruction = parseInstructionFile(string("TestData1.txt"));

	for(unsigned int i = 0; i < instruction.size(); i++) {
		instrPipe->cycle(instruction[i]);

		if(scoreboard->stopFound()) {
			scoreboard->cycleTillDone();
			break;
		}
	}

	return 0;
}
