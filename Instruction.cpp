#include "Instruction.h"

Instruction::Instruction(OpCodeEnum op, int I, int J, int K)
{
    fm = op;
    i = I;
    j = J;
    k = K;
    validInstruction = true;
}

Instruction::Instruction(void)
{
    i = -1;
    j = -1;
    k = -1;
    validInstruction = false;
}

OpCodeEnum Instruction::getFm(void)
{
    return fm;
}

int Instruction::getI(void)
{
    return i;
}

int Instruction::getJ(void)
{
    return j;
}

int Instruction::getK(void)
{
    return k;
}

bool Instruction::isValid(void)
{
    return validInstruction;
}

bool Instruction::isLong(void)
{
    return opCodeIsLong(fm);
}

bool opCodeIsLong(OpCodeEnum op)////////////THIS IS A PLACEHOLDER!
{
    return false;
}

void Instruction::setNoop() {
	fm = noop_INSTR;
	validInstruction = true;
}
