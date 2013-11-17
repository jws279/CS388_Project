#include "CDC6600Emulator.h"
#include "CDC7600Emulator.h"

int main() {
	CDCEmulator *emu = new CDC7600Emulator();

	delete emu;
	return 0;
}