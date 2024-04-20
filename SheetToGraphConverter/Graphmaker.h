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


#include <string>

class Graphmaker {
public:
    // Constructor
    Graphmaker() {}

    void processDataForDay(const std::string &filename, int day);
private:

};
#endif