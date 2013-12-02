#include "CDC6600Emulator.h"
#include "CDC7600Emulator.h"

int main() {
	// Run the CDC6600 Emulator
	CDCEmulator *emu = new CDC6600Emulator();
	emu->run();
	delete emu;

	// Run the CDC7600 Emulator
	emu = new CDC7600Emulator();
	emu->run();
	delete emu;

	char a;
	cin>>a;

	return 0;
}
