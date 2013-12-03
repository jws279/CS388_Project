#include "CDC7600Emulator.h"

CDC7600Emulator::CDC7600Emulator() {
	fetchDelay = 4;
    scoreboard = new Scoreboard7600(timingDiagram);
	instrPipe->setScoreboard(scoreboard);
}

CDC7600Emulator::~CDC7600Emulator() {
	delete scoreboard;
}

int CDC7600Emulator::run(string inname, string outname) {
	vector<Instruction> instruction = parseInstructionFile(inname);

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
			
			for(int k = cycleCount - 6; k < previousLoadCycle; k++) {
				instrPipe->cycle(noop);
				cycleCount++;
				timingDiagram->cycle();
			}

			previousLoadCycle = cycleCount;
		}

		instruction[i].setInstructionNumb(nextRow);

		if(instrPipe->cycle(instruction[i])) {
			nextRow = timingDiagram->addRow();
			packetCount += (instruction[i].isLong() ? 2 : 1);

			if(instruction[i].isLong()) {
				cycleCount++;
				timingDiagram->cycle();
				instrPipe->cycle(noop);
			}

			i++;
		}

		cycleCount++;
		timingDiagram->cycle();
	}

	scoreboard->cycleTillDone();

	timingDiagram->tableToCsv(outname);

	return 0;
}
