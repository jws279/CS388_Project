#ifndef INSTRUCTION_H
#define INSTRUCTION_H

typedef enum {
        no,  // no-op

} OpCodeEnum;

class Instruction
{
private:
    OpCodeEnum fm;
    int i;
    int* iPointer;
    int j;
    int* jPointer;
    int k;
    int* kPointer;
    bool isLongFormat;
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
    bool isLong(void);
    void setIPointer(int* iPointer);
    void setJPointer(int* jPointer);
    void setKPointer(int* kPointer);
    int getDereferencedI(void);
    int getDereferencedJ(void);
    int getDereferencedK(void);
    bool isValid(void);
};

#endif
