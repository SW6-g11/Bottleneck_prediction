#ifndef GRAPHMAKER_H
#define GRAPHMAKER_H
#include <string>
#include "sheetreader.h"
#include <iostream> 
#include "linkutils.h"
#include "traffic.h"
#include "path.h"
#include "router.h"
#include "link.h"
#include <string>

using namespace std;

class Graphmaker {
public:
    // Constructor
    Graphmaker() {}
    void processDataForDay(string &directoryPath, int day, int Limit);
};
#endif // GRAPHMAKER_H