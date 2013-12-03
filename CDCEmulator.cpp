#include "CDCEmulator.h"

CDCEmulator::CDCEmulator() : fetchDelay(0) {
	//timingDiagram = new TimingDiagram();
    instrPipe = new InstructionPipeline();
}

CDCEmulator::~CDCEmulator() {
	delete instrPipe;
	//delete timingDiagram;
}

int CDCEmulator::run(string inname, string outname) {

	return 0;
}
