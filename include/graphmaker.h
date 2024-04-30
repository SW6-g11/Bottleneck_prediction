#ifndef GRAPHMAKER_H
#define GRAPHMAKER_H
#include "sheetreader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <filesystem>
using namespace std;

class Graphmaker {
public:
    // Constructor
    Graphmaker() {}
    void processDataForDay(string &directoryPath, int day, int Limit);
};
#endif // GRAPHMAKER_H