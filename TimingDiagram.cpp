#include "TimingDiagram.h"

//Constructs blank timing diagram
TimingDiagram::TimingDiagram(int memAccessDelay)
{
	clockTickCount = -2; // To adjust timing table to start at 1
	this->memAccessDelay = memAccessDelay;
}

TimingDiagram::~TimingDiagram()
{
    for(unsigned int i=0; i < table.size(); i++)
    {
        delete table[i];
    }
}



//Writes the table to a csv file. Returns false on failure.
bool TimingDiagram::tableToCsv(string fileName)
{
    string tableString;
    char appendCStr[100];
    for(unsigned int i = 0; i < table.size(); i++)
    {
        for(int j = 0; j < TABLE_WIDTH; j++)
        {
            if(j > 0)
                tableString += ",";
            if(table[i][j] != -1)
            {
                sprintf(appendCStr, "%i", table[i][j]);
                string append = appendCStr;
                tableString += append;
                // tableString += (char)(table[i][j]) + '0';
            }
        }
        tableString += "\n";
    }
    ofstream fout;
    fout.open(fileName.c_str());
    if(!fout.is_open())
    {
        printf("Error opening output file!\n\r");
        return false;
    }
    fout << tableString;
    fout.close();
    return true;
}


//Adds a blank row to the table and returns the instructions index.
int TimingDiagram::addRow()
{
    int* row = new int[TABLE_WIDTH];
    std::fill_n(row, TABLE_WIDTH, -1);
    table.push_back(row);
    return table.size() - 1;
}


//Sets the issue time. Returns false if instNumb is invalid.
bool TimingDiagram::setIssue(int instNumb)
{
    if(table.size() < instNumb)
        return false;
    table[instNumb][ISSUE_INDEX] = clockTickCount;
    return true;
}


//Sets the start time. Returns false if instNumb is invalid.
bool TimingDiagram::setStart(int instNumb)
{
    if(table.size() < instNumb)
        return false;
    table[instNumb][START_INDEX] = clockTickCount;
    return true;
}


//Sets the result time. Returns false if instNumb is invalid.
bool TimingDiagram::setResult(int instNumb)
{
    if(table.size() < instNumb)
        return false;
    table[instNumb][RESULT_INDEX] = clockTickCount;
    return true;
}


//Sets the unit time. Returns false if instNumb is invalid.
bool TimingDiagram::setUnit(int instNumb)
{
    if(table.size() < instNumb)
        return false;
    table[instNumb][UNIT_INDEX] = clockTickCount;
    return true;
}


//Sets the fetch time. Returns false if instNumb is invalid.
bool TimingDiagram::setFetch(int instNumb)
{
    if(table.size() < instNumb)
        return false;
	table[instNumb][FETCH_INDEX] = clockTickCount + memAccessDelay;
    return true;
}


//Sets the store time. Returns false if instNumb is invalid.
bool TimingDiagram::setStore(int instNumb)
{
    if(table.size() < instNumb)
        return false;
	table[instNumb][STORE_INDEX] = clockTickCount + memAccessDelay;
    return true;
}

void TimingDiagram::cycle() {
	clockTickCount++;
}
