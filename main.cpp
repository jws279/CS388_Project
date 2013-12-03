#include "CDC6600Emulator.h"
#include "CDC7600Emulator.h"

int main() {
	// Run the CDC6600 Emulator
	/*CDCEmulator *emu = new CDC6600Emulator();
	emu->run("TestData1.txt", "6600Output1.csv");
	delete emu;*/

	// Run the CDC7600 Emulator
	CDCEmulator *emu = new CDC7600Emulator();
	emu->run("TestData2.txt", "7600Output2.csv");
	delete emu;

	return 0;
}
