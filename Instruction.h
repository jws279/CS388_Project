#ifndef INSTRUCTION_H
#define INSTRUCTION_H

typedef enum {
    stop,
    noop,
    branchIncrement,
    branchLongAdd,
    branchUnconditional,
    floatingAdd,
    floatingMultiply,
    floatingDivide,
    fixedAdd,
    increment,
    boolean,
    shift,
    populationCount,
    normalize,
} OpCodeEnum;

class Instruction
{
private:
    OpCodeEnum fm;
    int i;
    int j;
    int k;
    bool validInstruction;

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
};

#endif
