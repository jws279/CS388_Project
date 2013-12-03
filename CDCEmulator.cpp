#include "CDCEmulator.h"

CDCEmulator::CDCEmulator() : fetchDelay(0) {
    instrPipe = new InstructionPipeline();
}

CDCEmulator::~CDCEmulator() {
	delete instrPipe;
}

int CDCEmulator::run(string inname, string outname) {

	return 0;
}
