#ifndef FUNCTIONALUNIT_H
#define FUNCTIONALUNIT_H

#include "Instruction.h"
#include <stdio.h>
#include <math.h>


typedef enum {
    add_FU,
    multiply_FU,
    divide_FU,
    fixed_add_FU,
    increment_FU,
    pop_count_FU,
    boolean_FU,
    shift_FU,
    normalize_FU,
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
    int instructionIterator;


public:
    FunctionalUnit(int segment_time, int executionTime);  // 7600
    FunctionalUnit(int executionTime);  // 6600

    ~FunctionalUnit(void);

    bool resultReady(void);

    void resetResult(void);

    bool functionalUnitConflict(void);

    void clockTick(void);//Not sure if this should be public or private

    //This should be used for data dependencies where we need to load an instruction but not execute it.
    void setExecuteInstruction(bool execute);

    //Pushes the next instruction to the front and i onto the back.
    //This also executes clockTick() if it is a valid time to push an instruction
    //onto the pipeline. This assumes it is safe to push on an instruction.
    void pushPipeline(Instruction i);

    void print();

    //This is an accessor for the instructions in the functional unit's pipe.
    //Gets instruction at index i where 0 is the oldest instruction in the pipe
    Instruction getInstruction(int i);

    int getPipelineLength();

    //Returns true if an instruction has been issued to the functional unit
    //but is not being executed.
    bool getDontExecuteInstruction();
};


#endif
