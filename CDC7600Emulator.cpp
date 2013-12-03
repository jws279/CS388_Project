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
	int packetCount = 0;
	int previousLoadCycle = 1;
	int cycleCount = previousLoadCycle;

	Instruction noop;
	noop.setNoop();

	while(!scoreboard->stopFound()) {
		if(packetCount >= 4) {
			packetCount = 0;
			previousLoadCycle = cycleCount;
			
			for(int k = cycleCount - 8; k < previousLoadCycle; k++) {
				instrPipe->cycle(noop);
				cycleCount++;
				timingDiagram->cycle();
			}
		}

		instruction[i].setInstructionNumb(nextRow);

		if(instrPipe->cycle(instruction[i])) {
			nextRow = timingDiagram->addRow();
			i++;
			packetCount += (instruction[i].isLong() ? 2 : 1);
		}

		cycleCount++;
		timingDiagram->cycle();
	}

	scoreboard->cycleTillDone();

	timingDiagram->tableToCsv("Output.csv");

	return 0;
}
