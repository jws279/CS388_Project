#include "CDC6600Emulator.h"
#include "CDC7600Emulator.h"

int main() {
	// Run the CDC6600 Emulator on the first program
	CDCEmulator *emu = new CDC6600Emulator();
	emu->run("TestData1.txt", "6600Output1.csv");
	delete emu;

	// Run the CDC6600 Emulator on the second program
	emu = new CDC6600Emulator();
	emu->run("TestData2.txt", "6600Output2.csv");
	delete emu;

	// Run the CDC6600 Emulator on the third program
	emu = new CDC6600Emulator();
	emu->run("TestData3.txt", "6600Output3.csv");
	delete emu;

	// Run the CDC7600 Emulator on the first program
	emu = new CDC7600Emulator();
	emu->run("TestData1.txt", "7600Output1.csv");
	delete emu;
	
	// Run the CDC7600 Emulator on the second program
	emu = new CDC7600Emulator();
	emu->run("TestData2.txt", "7600Output2.csv");
	delete emu;

	// Run the CDC7600 Emulator on the third program
	emu = new CDC7600Emulator();
	emu->run("TestData3.txt", "7600Output3.csv");
	delete emu;


	return 0;
}
