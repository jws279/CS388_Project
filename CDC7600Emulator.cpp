#include "CDC7600Emulator.h"

CDC7600Emulator::CDC7600Emulator() {
	fetchDelay = 4;
}

CDC7600Emulator::~CDC7600Emulator() {
	
}

int CDC7600Emulator::run() {
	vector<Instruction> instruction = parseInstructionFile(string("TestData1.txt"));

	int i = 0;
	int nextRow = timingDiagram->addRow();
	while(!scoreboard->stopFound()) {
		instruction[i].setInstructionNumb(nextRow);
		if(instrPipe->cycle(instruction[i])) {
			nextRow = timingDiagram->addRow();
			i++;
		}
		timingDiagram->cycle();
	}

	scoreboard->cycleTillDone();

	timingDiagram->tableToCsv("Output.csv");

	return 0;
}
