#ifndef CDC7600EMULATOR_H
#define CDC7600EMULATOR_H

#include "CDCEmulator.h"
#include "Scoreboard7600.h"

class CDC7600Emulator : public CDCEmulator {
public:
	CDC7600Emulator();
	~CDC7600Emulator();
	virtual int run(string infile, string outfile);

private:
	Scoreboard *scoreboard;

};

#endif
