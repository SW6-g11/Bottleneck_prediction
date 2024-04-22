#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <filesystem>
#include "SheetToGraphConverter/Graphmaker.h"
// Line limit(for ram usage) 0 = unlimited(in theory)

using namespace std;

int main()
{
    string directoryPath = filesystem::current_path().string().append("/data/");
    int day = 1; // Change this variable to process different days
    int limit = 20;// Line limit(for ram usage) 0 = unlimited(in theory)
    // Create an instance of Graphmaker 
    Graphmaker GraphOne;

    // Process data for the specified day
    GraphOne.processDataForDay(directoryPath, day, limit);

    return 0;
}
