#ifndef CDC6600EMULATOR_H
#define CDC6600EMULATOR_H

#include "CDCEmulator.h"

class CDC6600Emulator : public CDCEmulator {
public:
	CDC6600Emulator();
	~CDC6600Emulator();
	virtual int run();

private:
	

};

#endif