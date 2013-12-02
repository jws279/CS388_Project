#include "Instruction.h"

Instruction::Instruction(OpCodeEnum op, int I, int J, int K, bool isLong)
{
    fm = op;
    i = I;
    j = J;
    k = K;
    longInstruction = isLong;
    validInstruction = true;
}

Instruction::Instruction(void)
{
    i = -1;
    j = -1;
    k = -1;
    validInstruction = false;
    longInstruction = false;
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
    return longInstruction;
}

void Instruction::setNoop() {
	fm = noop_INSTR;
	validInstruction = true;
}

void Instruction::setInstructionNumb(int numb)
{
    instructionNumb = numb;
}

int Instruction::getInstructionNumb()
{
    return instructionNumb;
}
