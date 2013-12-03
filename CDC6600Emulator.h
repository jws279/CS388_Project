#ifndef CDC6600EMULATOR_H
#define CDC6600EMULATOR_H

#include "CDCEmulator.h"
#include "Scoreboard6600.h"

class CDC6600Emulator : public CDCEmulator {
public:
	CDC6600Emulator();
	~CDC6600Emulator();
	virtual int run(string infile, string outfile);

private:
	Scoreboard *scoreboard;


};

#endif
