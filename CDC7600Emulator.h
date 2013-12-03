#ifndef CDC7600EMULATOR_H
#define CDC7600EMULATOR_H

#include "CDCEmulator.h"

class CDC7600Emulator : public CDCEmulator {
public:
	CDC7600Emulator();
	~CDC7600Emulator();
	virtual int run(string outname);

private:
	Scoreboard7600 *scoreboard;

};

#endif
