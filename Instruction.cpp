#include "Instruction.h"

Instruction::Instruction(OpCodeEnum op, int I, int J, int K, registerName iReg, registerName jReg, registerName kReg, bool isLong)
{
    fm = op;
    i = I;
    j = J;
    k = K;
    IReg = iReg;
    JReg = jReg;
    KReg = kReg;
    longInstruction = isLong;
    validInstruction = true;
}

Instruction::Instruction(void)
{
    i = -1;
    j = -1;
    k = -1;
    IReg = noRegister;
    JReg = noRegister;
    KReg = noRegister;
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

registerName Instruction::getIReg()
{
    return IReg;
}

registerName Instruction::getJReg()
{
    return JReg;
}

registerName Instruction::getKReg()
{
    return KReg;
}
