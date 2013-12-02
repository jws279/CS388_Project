#ifndef TIMING_DIAGRAM_H
#define TIMING_DIAGRAM_H


#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include "CDCEmulator.h"

#define TABLE_WIDTH 6


#define ISSUE_INDEX 0
#define START_INDEX 1
#define RESULT_INDEX 2
#define UNIT_INDEX 3
#define FETCH_INDEX 4
#define STORE_INDEX 5

using namespace std;

class TimingDiagram
{
private:
    vector<int*> table;

public:
    // TimingDiagram();
    ~TimingDiagram();
    bool tableToCsv(string fileName);
    int addRow();
    bool setIssue(int instNumb);
    bool setStart(int instNumb);
    bool setResult(int instNumb);
    bool setUnit(int instNumb);
    bool setFetch(int instNumb);
    bool setStore(int instNumb);
};




#endif
