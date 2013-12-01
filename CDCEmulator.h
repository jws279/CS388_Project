#ifndef CDCEMULATOR_H
#define CDCEMULATOR_H

#include <vector>
#include "Scoreboard7600.h"

class CDCEmulator {
public:
	CDCEmulator();
	~CDCEmulator();
	virtual int run();

private:
	//Vector<Instruction_t> instructionStack; //Not actually instructions, need to be 60-bit words
	Scoreboard7600 *scoreboard;

	//TableBuilder

protected:
	int fetchDelay;

};

#endif