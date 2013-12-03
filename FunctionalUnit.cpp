
#include "FunctionalUnit.h"

FunctionalUnit::FunctionalUnit(int segment_time, int executionTime)
{
	instructionIterator = 0;
    resultIsReady = false;
    dontExecuteInstruction = false;
    this->segmentTime = segment_time;
    this->executionTime = executionTime;
    pipelineLength = static_cast<int>(ceil(executionTime / static_cast<float>(segmentTime)));
    pipeline = new pipelineItem[pipelineLength];
    //Clear the pipeline
    for(int i=0; i < pipelineLength; i++)
    {
        pipeline[i].isValid = false;
    }
}

FunctionalUnit::FunctionalUnit(int executionTime)
{
	instructionIterator = 0;
    resultIsReady = false;
    dontExecuteInstruction = false;
    this->segmentTime = executionTime;
    this->executionTime = executionTime;
    pipelineLength = static_cast<int>(ceil(executionTime / static_cast<float>(segmentTime)));
    pipeline = new pipelineItem[pipelineLength];
    //Clear the pipeline
    for(int i=0; i < pipelineLength; i++)
    {
        pipeline[i].isValid = false;
    }
}

FunctionalUnit::~FunctionalUnit(void)
{
    //for(int i=0; i < pipelineLength; i++)
    //{
    //    delete &pipeline[i];
    //}
    delete pipeline;
}


void FunctionalUnit::clockTick(void)
{
    for(int i=0; i < pipelineLength; i++)
    {
        if(!(i == pipelineLength - 1 && dontExecuteInstruction))  // Make sure we don't push forward instructions which have halted execution for data dependency
        {
			//if(i == pipelineLength - 1) {
				//if(pipeline[i].isValid) {
				//	timingDiagram->setStart(pipeline[i].inst.getInstructionNumb());
				//}
			//}
            if(pipeline[i].isValid)
            {
				pipeline[i].clockTicks++;
                if(pipeline[i].clockTicks == executionTime)
                {
                    resultIsReady = true;
					if(pipeline[i].isValid) {
						timingDiagram->setResult(pipeline[i].inst.getInstructionNumb());
					}
                }
                else if(i > 0 && ( (pipeline[i].clockTicks % segmentTime) == 0) )
                {
					if(i == pipelineLength - 1 && pipeline[i].isValid) {
						timingDiagram->setUnit(pipeline[i].inst.getInstructionNumb());
					}
                    pipeline[i - 1] = pipeline[i];
                    pipeline[i].isValid = false;
                }
            }
        }
    }
}

bool FunctionalUnit::resultReady(void)
{
    bool ret = resultIsReady;
    resultIsReady = false;
    return ret;
}

void FunctionalUnit::resetResult(void)
{
    resultIsReady = false;
}

void FunctionalUnit::setExecuteInstruction(bool execute)
{
    dontExecuteInstruction = !execute;
}

void FunctionalUnit::pushPipeline(Instruction i)
{
    pipeline[pipelineLength - 1].isValid = true;
    pipeline[pipelineLength - 1].clockTicks = 0;
    pipeline[pipelineLength - 1].inst = i;
	
	timingDiagram->setIssue(i.getInstructionNumb());
}

void FunctionalUnit::print()
{
    for(int i=0; i < pipelineLength; i++)
    {
        printf("Pipeline Index: %i\n\r", i);
        printf("    isValid: %i\n\r", pipeline[i].isValid);
        printf("    clockTicks: %i\n\r", pipeline[i].clockTicks);
        printf("    Instruction OpCode: %i\n\r", pipeline[i].inst.getFm());
    }
}

bool FunctionalUnit::functionalUnitConflict(void)
{
    //Returns true if an instruction is in the back of the pipe
    return pipeline[pipelineLength - 1].isValid;
}

pipelineItem FunctionalUnit::getPipelineItem(int i) {
	if(i < 0)
    {
        //Allow for negative indexes
        i = getPipelineLength() + i;
    }
    return pipeline[i];
}

Instruction FunctionalUnit::getInstruction(int i)
{
    if(i < 0)
    {
        //Allow for negative indexes
        i = getPipelineLength() + i;
    }
    return pipeline[i].inst;
}

int FunctionalUnit::getPipelineLength()
{
    return pipelineLength;
}

bool FunctionalUnit::getDontExecuteInstruction()
{
    return dontExecuteInstruction;
}

void FunctionalUnit::setStartTime(Instruction instruction) {
	timingDiagram->setStart(instruction.getInstructionNumb());
}
