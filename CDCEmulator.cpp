#include "CDCEmulator.h"

CDCEmulator::CDCEmulator() : fetchDelay(0) {
	scoreboard = new Scoreboard7600();
	instrPipe = new InstructionPipeline(scoreboard);
}

CDCEmulator::~CDCEmulator() {
	delete scoreboard;
	delete instrPipe;
}

int CDCEmulator::run() {
	
	return 0;
}
