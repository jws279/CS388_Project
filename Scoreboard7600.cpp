
#include "Scoreboard7600.h"
#include "stdio.h"

Scoreboard7600()
{
    floatingAdder = FunctionalUnit(1, 4);
    multiplier = FunctionalUnit(2, 5);
    divider = FunctionalUnit(18, 20);
    fixedAdder = FunctionalUnit(1, 2);
    increment = FunctionalUnit(1, 2);
    boolean = FunctionalUnit(1, 2);
    popCount = FunctionalUnit(1, 2);
    shift = FunctionalUnit(1, 2);
    normalize = FunctionalUnit(1, 3);
}


//returns false on failure
//return true on success
bool receiveNextInstruction(Instruction inst)//////////ADD THINGS FOR DATA DEPENDENCY!!!
{
    success = false;
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
            success = floatingAdder.pipelineSlotAvailable()
            if(success)
            {
                floatingAdder.pushPipeline();
            }
            break;
        case floatingMultiply:

            break;
        case floatingDivide:

            break;
        case fixedAdd:

            break;
        case increment:

            break;
        case boolean:

            break;
        case shift:

            break;
        case populationCount:

            break;
        case normalize:

            break;
        default:
            printf("Error in scoreboard!\n\r");
    }
    if(success)
        clockTick();
    return success;
}

bool clockTick()
{

}

