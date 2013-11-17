
#include "FunctionalUnit.h"

FunctionalUnit::FunctionalUnit(void)
{
    result = -1;
    segmentTime = -1;
    executionTime = -1;
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
        if(pipeline[i].isValid)
        {
            if(pipeline[i].clockTicks == executionTime)
            {
                result = calculateResult(pipeline[i].inst);
            }
            else if(pipeline[i].clockTicks == segmentTime)
            {
                pipeline[i - 1] = pipeline[i];
                pipeline[i].isValid = false;
            }
        }
    }
}

bool FunctionalUnit::resultReady(void)
{
    // return pipeline[0].clockTicks == executionTime;
    return result != -1;
}

int FunctionalUnit::getResult(void)
{
    int ret = result;
    result = -1;
    return ret;
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
