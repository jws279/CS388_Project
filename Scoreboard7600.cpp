
#include "Scoreboard7600.h"
#include "stdio.h"

Scoreboard7600::Scoreboard7600(TimingDiagram *timingDiagram)
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
	functionalUnits[5] = booleaner;
	functionalUnits[6] = shifter;
	functionalUnits[7] = popCounter;
	functionalUnits[8] = normalizer;

	functionalUnits[0]->timingDiagram = timingDiagram;
	functionalUnits[1]->timingDiagram = timingDiagram;
	functionalUnits[2]->timingDiagram = timingDiagram;
	functionalUnits[3]->timingDiagram = timingDiagram;
	functionalUnits[4]->timingDiagram = timingDiagram;
	functionalUnits[5]->timingDiagram = timingDiagram;
	functionalUnits[6]->timingDiagram = timingDiagram;
	functionalUnits[7]->timingDiagram = timingDiagram;
	functionalUnits[8]->timingDiagram = timingDiagram;


    stop_found = false;
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

//returns false if pipeline should be halted and true otherwise
bool Scoreboard7600::receiveNextInstruction(Instruction inst)//SOME CASES NEED TO BE FINISHED
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
			fu = multiplier;
            break;
        case floatingDivide_INSTR:
			fu = divider;
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

void Scoreboard7600::clockTick()
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

bool Scoreboard7600::functionalUnitConflict(FunctionalUnit *fu)
{
	if(!fu) {
		return false;
	}
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
                printf("Write After Write!\n\r");
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
                    && functionalUnits[i]->getInstruction(j).getIReg() == inst.getKReg()))
                {
                    conflictExists = true;
                    printf("Read After Write! Instruction %i and %i\n\r", inst.getInstructionNumb(), functionalUnits[i]->getInstruction(j).getInstructionNumb());
                }
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
            printf("Write After Read!");
        }
    }

	return conflictExists;
}

bool Scoreboard7600::stopFound()
{
    return stop_found;
}

void Scoreboard7600::cycleTillDone()
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
