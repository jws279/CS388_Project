#include "CDC7600Emulator.h"

CDC7600Emulator::CDC7600Emulator() {
	fetchDelay = 4;
	timingDiagram = new TimingDiagram(fetchDelay);
    scoreboard = new Scoreboard7600(timingDiagram);
	instrPipe->setScoreboard(scoreboard);
}

CDC7600Emulator::~CDC7600Emulator() {
	delete scoreboard;
	delete timingDiagram;
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
		if(scoreboard->getbranchFound()) {
			int targetWord = scoreboard->getBranchTo();
			int currentWord = 0;
			
			packetCount = 0;
			previousLoadCycle = 1;
			cycleCount = previousLoadCycle;

			i = 0;
			while(currentWord < targetWord) {
				packetCount += (instruction[i].isLong() ? 2 : 1);

				if(packetCount >= 4) {
					packetCount = 0;
					currentWord++;
				}

				i++;
			}

			instrPipe->clearPipeline();

			for(int k = 0; k < 5; k++) {
				instrPipe->cycle(noop);
				timingDiagram->cycle();
			}
		}

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
