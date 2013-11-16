#include "instructionDefinitions.h"




class Instruction
{
private:
    int f;
    int m;
    int i;
    int j;
    int k;
    bool isLongFormat;

public:
    Instruction(OpCode op, int i, int j, int k)
    {

    }

    Instruction(int f, int m, int i, int j, int k)
    {

    }

    int getF(void)
    {
        return f;
    }

    int getM(void)
    {
        return m;
    }

    int getI(void)
    {
        return i;
    }

    int getJ(void)
    {
        return j;
    }

    unsigned int getK(void)
    {
        return k;
    }

    bool isLong(void)
    {
        return isLongFormat;
    }

    OpCode getOpCode(void)
    {
        return (f << 3) | m;
    }
}
