#include "CDCEmulator.h"

CDCEmulator::CDCEmulator() : fetchDelay(0) {
	scoreboard = new Scoreboard7600();
}

CDCEmulator::~CDCEmulator() {
	delete scoreboard;
}

int CDCEmulator::run() {
	
	return 0;
}
