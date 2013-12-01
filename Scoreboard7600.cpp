
#include "Scoreboard7600.h"
#include "stdio.h"

Scoreboard7600::Scoreboard7600()
{
    floatingAdder = new FunctionalUnit(1, 4);
    multiplier = new FunctionalUnit(2, 5);
    divider = new FunctionalUnit(18, 20);
    fixedAdder = new FunctionalUnit(1, 2);
    incrementer = new FunctionalUnit(1, 2);
    booleaner = new FunctionalUnit(1, 2);
    popCounter = new FunctionalUnit(1, 2);
    shifter = new FunctionalUnit(1, 2);
    normalizer = new FunctionalUnit(1, 3);

	functionalUnits = new FunctionalUnit*[num_FU];
	functionalUnits[0] = floatingAdder;
	functionalUnits[1] = multiplier;
	functionalUnits[2] = divider;
	functionalUnits[3] = fixedAdder;
	functionalUnits[4] = incrementer;
	functionalUnits[4] = booleaner;
	functionalUnits[5] = shifter;
	functionalUnits[6] = popCounter;
	functionalUnits[7] = normalizer;
}

Scoreboard7600::~Scoreboard7600() {
    delete floatingAdder;
    delete multiplier;
    delete divider;
    delete fixedAdder;
    delete incrementer;
    delete booleaner;
    delete popCounter;
    delete shifter;
    delete normalizer;
}

//returns false on failure
//return true on success
bool Scoreboard7600::receiveNextInstruction(Instruction inst)//SOME CASES NEED TO BE FINISHED
{
    bool success = true;
    FunctionalUnit *fu;
    switch(inst.getFm())
    {
        case noop_INSTR:
			success = true;
            break;
        case branchIncrement_INSTR:

            break;
        case branchLongAdd_INSTR:

            break;
        case branchUnconditional_INSTR:

            break;
        case floatingAdd_INSTR:
            fu = floatingAdder;
            break;
        case floatingMultiply_INSTR:

            break;
        case floatingDivide_INSTR:

            break;
        case fixedAdd_INSTR:
            fu = fixedAdder;
            break;
        case increment_INSTR:
            fu = incrementer;
            break;
        case boolean_INSTR:
            fu = booleaner;
            break;
        case shift_INSTR:
            fu = shifter;
            break;
        case populationCount_INSTR:
            fu = popCounter;
            break;
        case normalize_INSTR:
            fu = normalizer;
            break;
        default:
            printf("Error in scoreboard!\n\r");
            fu = 0;
            return false;
    }

    success &= !functionalUnitConflict(fu);
    if(success)
    {
        fu->pushPipeline(inst);
    }


    if(success)//?
        clockTick();
    return success;
}

void Scoreboard7600::clockTick()
{

}

bool Scoreboard7600::functionalUnitConflict(FunctionalUnit *fu)
{
    return fu->functionalUnitConflict();
}

bool Scoreboard7600::writeAfterWriteConflict(Instruction inst)
{
    int destinationRegister = inst.getI();
    bool conflictExists = false;
    //Check each instruction in each functional unit to make sure the destination
    //that instruction contains is not equal to the destination of inst.
    for(int i=0; i < sizeof(functionalUnits) / sizeof(functionalUnits[0]); i++)
    {
        for(int j=0; j < functionalUnits[i]->getPipelineLength(); j++)
        {
            if(functionalUnits[i]->getInstruction(j).getI() == destinationRegister)
            {
                conflictExists = true;
            }
        }
    }
    return conflictExists;
}

bool Scoreboard7600::readAfterWriteConflict(Instruction inst)
{
    int readRegisters[2];
    bool conflictExists = false;
    readRegisters[0] = inst.getJ();
    if(instIsLong(inst))
    {
        readRegisters[1] = inst.getK();
    }
    else
    {
        readRegisters[1] = -1;
    }
    //Check each instruction in each functional unit to make sure the instruction
    //is not writing to where instruction inst is reading from.
    for(int i=0; i < sizeof(functionalUnits) / sizeof(functionalUnits[0]); i++)
    {
        for(int j=0; j < functionalUnits[i]->getPipelineLength(); j++)
        {
            if(functionalUnits[i]->getInstruction(j).getI() == readRegisters[0] ||
                functionalUnits[i]->getInstruction(j).getI() == readRegisters[1])
            {
                conflictExists = true;
            }
        }
    }
    return conflictExists;
}

bool Scoreboard7600::writeAfterReadConflict(Instruction inst)
{
    bool conflictExists = false;
    for(int i=0; i < sizeof(functionalUnits) / sizeof(functionalUnits[0]); i++)
    {
        //Search for instructions in functional units that are issued but not started
        //and have inputs that are the destination register for instruction inst
        if(functionalUnits[i]->getDontExecuteInstruction() &&
            (functionalUnits[i]->getInstruction(-1).getJ() == inst.getI() ||
             functionalUnits[i]->getInstruction(-1).getK() == inst.getI()))
        {
            conflictExists = true;
        }
    }

	return conflictExists;
}

bool Scoreboard7600::instIsLong(Instruction inst)/////////////////////////////////THIS IS A PLACEHOLDER
{
    return false;
}
