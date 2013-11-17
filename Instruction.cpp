#include "Instruction.h"

Instruction::Instruction(OpCodeEnum op, int I, int J, int K)
{
    fm = op;
    i = I;
    j = J;
    k = K;
    iPointer = 0;
    jPointer = 0;
    kPointer = 0;
    isLongFormat = false;///////////////////////////////
    validInstruction = true;
}

Instruction::Instruction(void)
{
    i = -1;
    j = -1;
    k = -1;
    validInstruction = false;
    iPointer = 0;
    jPointer = 0;
    kPointer = 0;
    isLongFormat = false;
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

bool Instruction::isLong(void)
{
    return isLongFormat;
}

void Instruction::setIPointer(int* ip)
{
    iPointer = ip;
}

void Instruction::setJPointer(int* jp)
{
    jPointer = jp;
}

void Instruction::setKPointer(int* kp)
{
    kPointer = kp;
}

int Instruction::getDereferencedI(void)
{
    return *iPointer;
}

int Instruction::getDereferencedJ(void)
{
    return *jPointer;
}

int Instruction::getDereferencedK(void)
{
    return *kPointer;
}

bool Instruction::isValid(void)
{
    return validInstruction;
}
