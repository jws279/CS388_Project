#include "CDC7600Emulator.h"

CDC7600Emulator::CDC7600Emulator() {
	fetchDelay = 4;
}

CDC7600Emulator::~CDC7600Emulator() {
	
}

int CDC7600Emulator::run() {
	vector<Instruction> instruction = parseInstructionFile(string("TestData1.txt"));

	int i = 0;
	while(!scoreboard->stopFound()) {
		if(instrPipe->cycle(instruction[i])) {
			i++;
		}
	}

	scoreboard->cycleTillDone();


	return 0;
}
