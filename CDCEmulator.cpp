#include "CDCEmulator.h"

CDCEmulator::CDCEmulator() : fetchDelay(0) {
	timingDiagram = new TimingDiagram();
    scoreboard = new Scoreboard7600(timingDiagram);
    instrPipe = new InstructionPipeline(scoreboard);
}

CDCEmulator::~CDCEmulator() {
	delete scoreboard;
	delete instrPipe;
}

int CDCEmulator::run() {

	return 0;
}


//int CDCEmulator::clockTickCount = 0;
