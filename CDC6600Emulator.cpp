#include "CDC6600Emulator.h"

CDC6600Emulator::CDC6600Emulator()  {
	// Initialize
	fetchDelay = 5;
	timingDiagram = new TimingDiagram(fetchDelay);
    scoreboard = new Scoreboard6600(timingDiagram);
	instrPipe->setScoreboard(scoreboard);
}

CDC6600Emulator::~CDC6600Emulator() {
	// Clean up
	delete scoreboard;
	delete timingDiagram;
}

int CDC6600Emulator::run(string inname, string outname) {
	// Set up
	vector<Instruction> instruction = parseInstructionFile(inname);

	int i = 0;
	int nextRow = timingDiagram->addRow();
	int packetCount = 0;
	int previousLoadCycle = 1;
	int cycleCount = previousLoadCycle;

	Instruction noop;
	noop.setNoop();

	// Push instructions onto pipeline until program stop found
	while(!scoreboard->stopFound()) {
		// If branch to be taken found, clear pipeline and find next instruction
		if(scoreboard->getbranchFound()) {
			int targetWord = scoreboard->getBranchTo();
			int currentWord = 0;
			
			packetCount = 0;
			previousLoadCycle = 1;
			cycleCount = previousLoadCycle;

			i = 0;
			// Find instruction
			while(currentWord < targetWord) {
				packetCount += (instruction[i].isLong() ? 2 : 1);

				if(packetCount >= 4) {
					packetCount = 0;
					currentWord++;
				}

				i++;
			}

			instrPipe->clearPipeline();
			
			// Execute over wait time for jump
			for(int k = 0; k < 5; k++) {
				instrPipe->cycle(noop);
				timingDiagram->cycle();
			}
		}

		// If finished a word, cycle till next is ready
		if(packetCount >= 4) {
			packetCount = 0;
			
			for(int k = cycleCount - 8; k < previousLoadCycle; k++) {
				instrPipe->cycle(noop);
				cycleCount++;
				timingDiagram->cycle();
			}

			previousLoadCycle = cycleCount;
		}

		// Set instruction number for timingDiagram
		instruction[i].setInstructionNumb(nextRow);

		// Attempt to push next instruction
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

		// Increment cycle count here and in timingDiagram
		cycleCount++;
		timingDiagram->cycle();
	}

	// Wrap up remaining instructions
	scoreboard->cycleTillDone();

	// Output file
	timingDiagram->tableToCsv(outname);

	return 0;
}
