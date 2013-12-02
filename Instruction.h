#ifndef INSTRUCTION_H
#define INSTRUCTION_H

typedef enum {
    invalid_INSTR,
    stop_INSTR,
    noop_INSTR,
    branchIncrement_INSTR,
    branchLongAdd_INSTR,
    branchUnconditional_INSTR,
    floatingAdd_INSTR,
    floatingMultiply_INSTR,
    floatingDivide_INSTR,
    fixedAdd_INSTR,
    fixedLongAdd_INSTR,
    increment_INSTR,
    boolean_INSTR,
    shift_INSTR,
    shiftNormalize_INSTR,
    populationCount_INSTR,
    normalize_INSTR,
} OpCodeEnum;

class Instruction
{
private:
    OpCodeEnum fm;
    int i;
    int j;
    int k;
    int instructionNumb;  // This is the index of the instruction in the code
    bool validInstruction;
    bool longInstruction;

public:
    //Creates a valid instruction
    Instruction(OpCodeEnum op, int i, int j, int k);
    //Creates an invalid instruction
    Instruction(void);
    OpCodeEnum getFm(void);
    int getI(void);
    int getJ(void);
    int getK(void);
    bool isValid(void);
    bool isLong();
	void setNoop();
    void setInstructionNumb(int numb);
    int getInstructionNumb();
};

bool opCodeIsLong(OpCodeEnum op);

#endif
