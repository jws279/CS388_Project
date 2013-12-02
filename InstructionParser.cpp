#include "InstructionParser.h"


//Takes in a filename and converts the octal lines it holds into a vector of Instruction objects
vector<Instruction> parseInstructionFile(string fileName)
{
    vector<Instruction> v;
    char buf[64];
    ifstream fin(fileName.c_str(), std::ifstream::in);
    if(!fin.good())
    {
        printf("Unable to open instruction file!\n\r");
        return v;
    }

    while(!fin.eof())
    {
        fin.getline(buf, MAX_CHARS_PER_LINE+10);
        if(fin.gcount() > 1)
        {
            printf("line: %s\n\r", buf);
            //Check to be sure line is valid
            for(int i = 0; i < MAX_CHARS_PER_LINE; i++)
            {
                buf[i] -= '0';  // Convert from ascii
                if(buf[i] < 0 || buf[i] > 7)
                {
                    printf("Error in instruction file! buf[%i] = %i\n\r", i, buf[i]);
                    return v;
                }
            }
            int offset = 0;
            while(offset < 19)
            {
                OpCodeEnum op = invalid_INSTR;
                int i = -1;
                int j = -1;
                int k = -1;
    			cout<<"buffer: "<<(char)(buf[offset + 0]+'0')<<endl;
                //Get the parse the op code
                switch(buf[offset + 0])
                {
                    case 0:  // Branch
                        switch(buf[offset + 1])
                        {
                            case 0:
                                op = stop_INSTR;
                                break;
                            case 1:
                            case 2:
                                op = branchUnconditional_INSTR;
                                break;
                            case 3:
                                op = branchLongAdd_INSTR;
                                break;
                            default: // 04 - 07
                                op = branchIncrement_INSTR;
                                break;
                        }
                        break;
                    case 1:  // Boolean
                        op = boolean_INSTR;
                        break;
                    case 2:  // Shift
                        switch(buf[offset + 1])
                        {
                            case 0:
                            case 1:
                            case 2:
                            case 3:
                            case 6:
                            case 7:
                                op = shift_INSTR;
                                break;
                            case 4:
                            case 5:
                                op = shiftNormalize_INSTR;
                                break;
                        }
                        break;
                    case 3:  // Add (standard or long)
                        switch(buf[offset + 1])
                        {
                            case 0:
                            case 1:
                            case 2:
                            case 3:
                            case 4:
                            case 5:
                                op = fixedAdd_INSTR;
                                break;
                            case 6:
                            case 7:
                                op = fixedLongAdd_INSTR;
                                break;
                        }
                        break;
                    case 4:  // Divide or Shift
                        switch(buf[offset + 1])
                        {
                            case 0:
                            case 1:
                            case 2:
                                op = floatingMultiply_INSTR;
                                break;
                            case 3:
                                op = shift_INSTR;
                                break;
                            case 4:
                            case 5:
                                op = floatingDivide_INSTR;
                                break;
                            case 6:
                                op = noop_INSTR;
                                break;
                            case 7:
                                op = populationCount_INSTR;
                                break;
                        }
                        break;
                    default:  // Increment
                        op = increment_INSTR;
                        break;
                }

                i = buf[offset + 2];
                j = buf[offset + 3];
                if(opCodeIsLong(op))
                {
                    k = (buf[offset + 4] << 15) | (buf[offset + 5] << 12) | (buf[offset + 6] << 9) |
                        (buf[offset + 7] << 6) | (buf[offset + 7] << 3) | buf[offset + 3];
                    offset += 10;  // offset 10 characters (30 bits)
                }
                else
                {
                    k = buf[offset + 4];
                    offset += 5;  // offset 5 characters (15 bits)
                }

                Instruction inst(op, i, j, k);
                v.push_back(inst);

            }
        }
    }
    fin.close();
    return v;
}
