
#include "FunctionalUnit.h"

FunctionalUnit::FunctionalUnit(int segment_time, int executionTime)
{
    resultIsReady = false;
    dontExecuteInstruction = false;
    segmentTime = segment_time;
    executionTime = executionTime;
    pipelineLength = static_cast<int>(ceil(segmentTime / static_cast<float>(executionTime)));
    pipeline = new pipelineItem[pipelineLength];
    //Clear the pipeline
    for(int i=0; i < pipelineLength; i++)
    {
        pipeline[i].isValid = false;
    }
}

FunctionalUnit::FunctionalUnit(int executionTime)
{
    resultIsReady = false;
    segmentTime = executionTime;
    executionTime = executionTime;
    pipelineLength = static_cast<int>(ceil(segmentTime / static_cast<float>(executionTime)));
    pipeline = new pipelineItem[pipelineLength];
    //Clear the pipeline
    for(int i=0; i < pipelineLength; i++)
    {
        pipeline[i].isValid = false;
    }
}

FunctionalUnit::~FunctionalUnit(void)
{
    for(int i=0; i < pipelineLength; i++)
    {
        delete &pipeline[i];
    }
    delete[] pipeline;
}


void FunctionalUnit::clockTick(void)
{
    for(int i=0; i < pipelineLength; i++)
    {
        if(!(i == pipelineLength - 1 && dontExecuteInstruction))  // Make sure we don't push forward instructions which have halted execution for data dependency
        {
            if(pipeline[i].isValid)
            {
                if(pipeline[i].clockTicks == executionTime)
                {
                    resultIsReady = true;
                }
                else if(pipeline[i].clockTicks == segmentTime)
                {
                    pipeline[i - 1] = pipeline[i];
                    pipeline[i].isValid = false;
                }
            }
        }
    }
}

bool FunctionalUnit::resultReady(void)
{
    int ret = resultIsReady;
    resultIsReady = false;
    return ret;
}

int FunctionalUnit::resetResult(void)
{
    resultIsReady = false;
}

void FunctionalUnit::setExecuteInstruction(bool execute)
{
    dontExecuteInstruction = !execute;
}

int FunctionalUnit::pushPipeline(Instruction i)
{
    if(pipelineSlotAvailable())
    {
        clockTick();
        pipeline[pipelineLength - 1].isValid = true;
        pipeline[pipelineLength - 1].clockTicks = 0;
        pipeline[pipelineLength - 1].inst = i;
        return 1;
    }
    return 0;
}

void FunctionalUnit::pushPipeline()
{
    clockTick();
    pipeline[pipelineLength - 1].isValid = false;
}

void FunctionalUnit::print()
{
    for(int i=0; i < pipelineLength; i++)
    {
        printf("Pipeline Index: %i\n\r", i);
        printf("    isValid: %i", pipeline[i].isValid);
        printf("    clockTicks: %i", pipeline[i].clockTicks);
        printf("    Instruction OpCode: %i", pipeline[i].inst.getFm());
    }
}

bool FunctionalUnit::pipelineSlotAvailable(void)
{
    return !pipeline[pipelineLength - 1].isValid;
}
