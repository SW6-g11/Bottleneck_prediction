#ifndef GRAPHMAKER_H
#define GRAPHMAKER_H
#include "sheetreader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <filesystem>
#include <graphDataStruct.h>
using namespace std;

class Graphmaker
{
public:
    // Constructor
    Graphmaker() {}
    void processDataForDay(string &directoryPath, int day, int Limit, graphDataStruct &graphData);
};
#endif // GRAPHMAKER_H