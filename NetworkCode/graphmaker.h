#ifndef GRAPHMAKER_H
#define GRAPHMAKER_H
#include "sheetreader.h"
#include "linkutils.h"
#include "traffic.h"
#include "path.h"
#include "router.h"
#include "link.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <filesystem>

class Graphmaker {
public:
    // Constructor
    Graphmaker() {}

    void processDataForDay(const std::string &filename, int day);
};
#endif //GRAPHMAKER_H
