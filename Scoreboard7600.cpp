
#include "Scoreboard7600.h"
#include "stdio.h"

Scoreboard7600::Scoreboard7600()
{
    floatingAdder = FunctionalUnit(1, 4);
    multiplier = FunctionalUnit(2, 5);
    divider = FunctionalUnit(18, 20);
    fixedAdder = FunctionalUnit(1, 2);
    incrementer = FunctionalUnit(1, 2);
    booleaner = FunctionalUnit(1, 2);
    popCounter = FunctionalUnit(1, 2);
    shifter = FunctionalUnit(1, 2);
    normalizer = FunctionalUnit(1, 3);
}


//returns false on failure
//return true on success
bool Scoreboard7600::receiveNextInstruction(Instruction inst)//SOME CASES NEED TO BE FINISHED
{
    success = true;
    functionalUnit fu;
    switch(inst.fm)
    {
        case noop:
        success = true;
            break;
        case branchIncrement:

            break;
        case branchLongAdd:

            break;
        case branchUnconditional:

            break;
        case floatingAdd:
            fu = floatingAdder;
            break;
        case floatingMultiply:

            break;
        case floatingDivide:

            break;
        case fixedAdd:
            fu = fixedAdder;
            break;
        case increment:
            fu = incrementer;
            break;
        case boolean:
            fu = booleaner;
            break;
        case shift:
            fu = shifter;
            break;
        case populationCount:
            fu = popCounter;
            break;
        case normalize:
            fu = normalizer;
            break;
        default:
            printf("Error in scoreboard!\n\r");
            fu = 0;
            return;
    }

    success &= !functionalUnitConflict(fu);
    if(success)
    {
        fu.pushPipeline(inst);
    }


    if(success)//?
        clockTick();
    return success;
}

bool Scoreboard7600::clockTick()
{

}

bool Scoreboard7600::functionalUnitConflict(FunctionalUnit fu)
{
    return fu.functionalUnitConflict();
}

bool Scoreboard7600::writeAfterWriteConflict(Instruction inst)
{
    int destinationRegister = inst.getI();
    bool conflictExists = false;
    //Check each instruction in each functional unit to make sure the destination
    //that instruction contains is not equal to the destination of inst.
    for(int i=0; i < sizeof(functionalUnits) / sizeof(functionalUnits[0]), i++)
    {
        for(int j=0; j < functionalUnits[i].getPipelineLength(); j++)
        {
            if(functionalUnits[i].getInstruction(j).getI() == destinationRegister)
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
    for(int i=0; i < sizeof(functionalUnits) / sizeof(functionalUnits[0]), i++)
    {
        for(int j=0; j < functionalUnits[i].getPipelineLength(); j++)
        {
            if(functionalUnits[i].getInstruction(j).getI() == readRegisters[0] ||
                functionalUnits[i].getInstruction(j).getI() == readRegisters[1])
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
    for(int i=0; i < sizeof(functionalUnits) / sizeof(functionalUnits[0]), i++)
    {
        //Search for instructions in functional units that are issued but not started
        //and have inputs that are the destination register for instruction inst
        if(functionalUnits[i].getDontExecuteInstruction() &&
            (functionalUnits[i].getInstruction(-1).getJ() == inst.getI() ||
             functionalUnits[i].getInstruction(-1).getK() == inst.getI())
        {
            conflictExists = true;
        }
    }
}

bool Scoreboard7600::instIsLong(Instruction inst)/////////////////////////////////THIS IS A PLACEHOLDER
{
    return false;
}
