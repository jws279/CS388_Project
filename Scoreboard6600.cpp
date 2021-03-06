
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
    shifter = new FunctionalUnit(3, 3);
    brancher = new FunctionalUnit(8, 8);

    functionalUnits = new FunctionalUnit*[num_FU];
    functionalUnits[0] = multiplier1;
    functionalUnits[1] = multiplier2;
    functionalUnits[2] = divider;
    functionalUnits[3] = floatingAdder;
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

	this->timingDiagram = timingDiagram;

    stop_found = false;
	branchFound = false;
	branchTo = 0;
	numBranches = 5;
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
			if(numBranches > 0) {
				branchFound = true;
				branchTo = inst.getK();
				fu = brancher;
				numBranches--;
			}
			else {
				inst.setNoop();
			}
            break;
        case branchLongAdd_INSTR:
			if(numBranches > 0) {
				branchFound = true;
				branchTo = inst.getK();
				fu = brancher;
				numBranches--;
			}
			else {
				inst.setNoop();
			}
            break;
        case branchUnconditional_INSTR:
			if(numBranches > 0) {
				branchFound = true;
				branchTo = inst.getK();
				fu = brancher;
				numBranches--;
			}
			else {
				inst.setNoop();
			}
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
            break;
        case normalize_INSTR:
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
        functionalUnits[i]->clockTick();
        Instruction inst = functionalUnits[i]->getInstruction(functionalUnits[i]->getPipelineLength()-1);
        if(inst.isValid() && functionalUnits[i]->getDontExecuteInstruction() && !readAfterWriteConflict(inst)) {
            functionalUnits[i]->setStartTime(inst);
            functionalUnits[i]->setExecuteInstruction(true);
        }
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
    for(int i=0; i < num_FU; i++)
    {
        for(int j=0; j < functionalUnits[i]->getPipelineLength(); j++)
        {
			Instruction tempInst = functionalUnits[i]->getInstruction(j);
            if(functionalUnits[i]->getPipelineItem(j).isValid && tempInst.isValid() && inst.getInstructionNumb() != tempInst.getInstructionNumb())
            {
                if((tempInst.getI() == readRegisters[0] && tempInst.getIReg() == inst.getJReg())
                    || (tempInst.getI() == readRegisters[1] && tempInst.getIReg() == inst.getKReg())
					|| (tempInst.getIReg() == xRegister && inst.getIReg() == aRegister && tempInst.getI() == inst.getI())
					&& (inst.getKReg() != noRegister || inst.getJReg() != noRegister))
                {
                    conflictExists = true;
                    printf("Read After Write! Instruction %i and %i\n\r", inst.getInstructionNumb(), functionalUnits[i]->getInstruction(j).getInstructionNumb());
					break;
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
		timingDiagram->cycle();
        done = true;
        for(int i = 0; i < num_FU; i++) {
            FU_busy = false;
            for(int j = 0; j < functionalUnits[i]->getPipelineLength(); j++) {
                FU_busy |= functionalUnits[i]->getPipelineItem(j).isValid;
            }
            done &= !FU_busy;
        }
    };

    return;
}

void Scoreboard6600::flushPipelines()
{
    for(int i=0; i < sizeof(functionalUnits) / sizeof(functionalUnits[0]); i++)
    {
        functionalUnits[i]->getPipelineLength();
    }
}

bool Scoreboard6600::getbranchFound(){
	bool ret = branchFound;
	branchFound = false;
	return ret;
}
int Scoreboard6600::getBranchTo() {
	return branchTo;
}
