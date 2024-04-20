#ifndef GRAPHMAKER_H
#define GRAPHMAKER_H
#include <string>
#include "SheetReader.h"
#include <iostream> 
#include "Linkutils.h"
#include "Traffic.h"
#include "Path.h"
#include "Router.h"
#include "Link.h"

template <typename T>
#include <string>

class Graphmaker {
public:
    // Constructor
    Graphmaker(const std::string &directoryPath);

    void processDataForDay(const std::string &filename, int day);
private:

};
#endif