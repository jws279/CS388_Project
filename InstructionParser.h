#ifndef INSTRUCTION_PARSER_H
#define INSTRUCTION_PARSER_H

#include "Instruction.h"
#include "stdio.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define MAX_CHARS_PER_LINE 20

using namespace std;

vector<Instruction> parseInstructionFile(string s);




#endif
