#ifndef FUNCTIONALUNIT_H
#define FUNCTIONALUNIT_H

#include "Instruction.h"
#include <stdio.h>
#include <math.h>


typedef enum {
    add,
    multiply,
    divide,
    fixed_add,
    increment,
    pop_count,
    boolean,
    shift,
    normalize,
} functionalUnitEnum;


typedef struct
{
    Instruction inst;  //Instruction that is in the stage of the pipeline
    int clockTicks;    //How long it has been in the pipeline
    bool isValid;      //False if it is not a legit instruction
} pipelineItem;


class FunctionalUnit
{
private:
    bool resultIsReady;
    int segmentTime;
    int executionTime;
    int pipelineLength;
    bool dontExecuteInstruction;
    pipelineItem *pipeline;
    functionalUnitEnum unitType;
    virtual int calculateResult(Instruction inst)=0;


public:
    FunctionalUnit(int segment_time, int executionTime);  // 7600
    FunctionalUnit(int executionTime);  // 6600

    ~FunctionalUnit(void);

    bool resultReady(void);

    void resetResult(void);

    bool pipelineSlotAvailable(void);

    void clockTick(void);//Not sure if this should be public or private

    //This should be used for data dependencies where we need to load an instruction but not execute it.
    void setExecuteInstruction(bool execute);

    //Pushes the next instruction to the front and i onto the back.
    //Returns 1 on success. Returns 0 if a new instruction cannot be pushed yet.
    //This also executes clockTick() if it is a valid time to push an instruction
    //onto the pipeline.
    int pushPipeline(Instruction i);

    //Pushes the next instruction to the front and null onto the back.
    //This also executes clockTick()
    void pushPipeline();

    void print();
};


#endif
