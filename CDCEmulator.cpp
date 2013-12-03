#include "CDCEmulator.h"

CDCEmulator::CDCEmulator() : fetchDelay(0) {
	timingDiagram = new TimingDiagram();
    /*scoreboard = new Scoreboard7600(timingDiagram);*/
    instrPipe = new InstructionPipeline(/*scoreboard*/);
}

CDCEmulator::~CDCEmulator() {
	//delete scoreboard;
	delete instrPipe;
	delete timingDiagram;
}

int CDCEmulator::run(string outname) {
	/*vector<Instruction> instruction = parseInstructionFile(string("TestData1.txt"));

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
			
			for(int k = cycleCount - 8; k < previousLoadCycle; k++) {
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

	timingDiagram->tableToCsv("Output.csv");*/

	return 0;
}
