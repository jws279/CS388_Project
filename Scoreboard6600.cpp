
#include "Scoreboard6600.h"
#include "stdio.h"

Scoreboard6600::Scoreboard6600(TimingDiagram *timingDiagram)
{
    floatingAdder = new FunctionalUnit(4, 4);
    multiplier1 = new FunctionalUnit(10, 10);
    multiplier2 = new FunctionalUnit(10, 10);
    divider = new FunctionalUnit(29, 29);
    fixedAdder = new FunctionalUnit(3, 3);
    incrementer1 = new FunctionalUnit(3, 3);
    incrementer2 = new FunctionalUnit(3, 3);
    booleaner = new FunctionalUnit(3, 3);
    shifter = new FunctionalUnit(3, 3);  // 3 cycles is a simplification
    brancher = new FunctionalUnit(8, 8);  // 8 cycles is a simplification

    functionalUnits = new FunctionalUnit*[num_FU];
    functionalUnits[0] = floatingAdder;
    functionalUnits[1] = multiplier1;
    functionalUnits[2] = multiplier2;
    functionalUnits[3] = divider;
    functionalUnits[4] = fixedAdder;
    functionalUnits[5] = incrementer1;
    functionalUnits[6] = incrementer2;
    functionalUnits[7] = booleaner;
    functionalUnits[8] = shifter;
    functionalUnits[9] = brancher;

    functionalUnits[0]->timingDiagram = timingDiagram;
    functionalUnits[1]->timingDiagram = timingDiagram;
    functionalUnits[2]->timingDiagram = timingDiagram;
    functionalUnits[3]->timingDiagram = timingDiagram;
    functionalUnits[4]->timingDiagram = timingDiagram;
    functionalUnits[5]->timingDiagram = timingDiagram;
    functionalUnits[6]->timingDiagram = timingDiagram;
    functionalUnits[7]->timingDiagram = timingDiagram;
    functionalUnits[8]->timingDiagram = timingDiagram;
    functionalUnits[9]->timingDiagram = timingDiagram;


    stop_found = false;
}

Scoreboard6600::~Scoreboard6600() {
    delete floatingAdder;
    delete multiplier1;
    delete multiplier2;
    delete divider;
    delete fixedAdder;
    delete incrementer1;
    delete incrementer2;
    delete booleaner;
    delete shifter;
    delete brancher;
}

//returns false if pipeline should be halted and true otherwise
bool Scoreboard6600::receiveNextInstruction(Instruction inst)//SOME CASES NEED TO BE FINISHED
{
    bool haltPipeline = false;
    FunctionalUnit *fu = 0;
    switch(inst.getFm())
    {
        case invalid_INSTR:
            printf("Invalid instruction found!\n\r");
            haltPipeline = false;
            break;
        case stop_INSTR:
            stop_found = true;
            haltPipeline = true;
            cout<<inst.getFm()<<" "<<inst.getI()<<" "<<inst.getJ()<<" "<<inst.getK()<<endl;
            break;
        case noop_INSTR:
            haltPipeline = false;
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
            fu = multiplier1;
            if(functionalUnitConflict(fu))
                fu = multiplier2;
            break;
        case floatingDivide_INSTR:
            fu = divider;
            break;
        case fixedAdd_INSTR:
            fu = fixedAdder;
            break;
        case increment_INSTR:
            fu = incrementer1;
            if(functionalUnitConflict(fu))
                fu = incrementer2;
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

    if(inst.getFm() != invalid_INSTR)
    {
        clockTick();
        haltPipeline |= functionalUnitConflict(fu);
        if(!haltPipeline && inst.getFm() != noop_INSTR)
        {
            cout<<inst.getFm()<<" "<<inst.getI()<<" "<<inst.getJ()<<" "<<inst.getK()<<endl;
            fu->pushPipeline(inst);

            if(!readAfterWriteConflict(inst)) {
                fu->setStartTime(inst);
                fu->setExecuteInstruction(true);
            }
            else {
                fu->setExecuteInstruction(false);
            }
        }
    }
    return !haltPipeline;
}

void Scoreboard6600::clockTick()
{
    for(int i = 0; i < num_FU; i++)
    {
        Instruction inst = functionalUnits[i]->getInstruction(functionalUnits[i]->getPipelineLength()-1);
        if(inst.isValid() && functionalUnits[i]->getDontExecuteInstruction() && !readAfterWriteConflict(inst)) {
            functionalUnits[i]->setStartTime(inst);
            functionalUnits[i]->setExecuteInstruction(true);
        }
        functionalUnits[i]->clockTick();
    }
}

bool Scoreboard6600::functionalUnitConflict(FunctionalUnit *fu)
{
    if(!fu) {
        return false;
    }
    return fu->functionalUnitConflict();
}

bool Scoreboard6600::writeAfterWriteConflict(Instruction inst)
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
                printf("Write After Write!\n\r");
            }
        }
    }
    return conflictExists;
}

bool Scoreboard6600::readAfterWriteConflict(Instruction inst)
{
    int readRegisters[2];
    bool conflictExists = false;
    readRegisters[0] = inst.getJ();
    if(inst.isLong())
    {
        readRegisters[1] = -1;
    }
    else
    {
        readRegisters[1] = inst.getK();
    }
    //Check each instruction in each functional unit to make sure the instruction
    //is not writing to where instruction inst is reading from.
    for(int i=0; i < sizeof(functionalUnits) / sizeof(functionalUnits[0]); i++)
    {
        for(int j=0; j < functionalUnits[i]->getPipelineLength(); j++)
        {
            if(inst.getInstructionNumb() != functionalUnits[i]->getInstruction(j).getInstructionNumb())
            {
                if((functionalUnits[i]->getInstruction(j).getI() == readRegisters[0]
                    && functionalUnits[i]->getInstruction(j).getIReg() == inst.getJReg())
                    || (functionalUnits[i]->getInstruction(j).getI() == readRegisters[1]
                    && functionalUnits[i]->getInstruction(j).getIReg() == inst.getKReg())
                        && (inst.getKReg() != noRegister || inst.getJReg() != noRegister))
                {
                    conflictExists = true;
                    printf("Read After Write! Instruction %i and %i\n\r", inst.getInstructionNumb(), functionalUnits[i]->getInstruction(j).getInstructionNumb());
                }
            }
        }
    }
    return conflictExists;
}

bool Scoreboard6600::writeAfterReadConflict(Instruction inst)
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
            printf("Write After Read!");
        }
    }

    return conflictExists;
}

bool Scoreboard6600::stopFound()
{
    return stop_found;
}

void Scoreboard6600::cycleTillDone()
{
    bool done = false;
    bool FU_busy = false;
    while(!done){
        clockTick();
        done = true;
        for(int i = 0; i < num_FU; i++) {
            FU_busy = false;
            for(int j = 0; j < functionalUnits[i]->getPipelineLength(); j++) {
                if(j != 0) {
                    FU_busy |= functionalUnits[i]->getPipelineItem(j).isValid;
                }
                else {
                    FU_busy |= (functionalUnits[i]->getPipelineItem(j).isValid && functionalUnits[i]->resultReady());
                }
            }
            done &= !FU_busy;
        }
    };

    return;
}
