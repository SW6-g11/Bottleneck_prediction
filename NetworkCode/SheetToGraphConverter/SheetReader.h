#ifndef SHEETREADER_H
#define SHEETREADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <filesystem>
#include "path.h"
#include "Link.h"
#include "Router.h"
#include "Inputverifyer.h"
#include "linkutils.h"
#include "Traffic.h"
// class Linkutils;
// class Traffic;
// class Paths;
// class Router;
// class Link;

#define DEFAULTLIMIT 100

using namespace std;

class SheetReader {
public:
    // Constructor(s), destructor, and any other public members
    // overloading constructor (have one use the other) gives us an optional input "limit"
    SheetReader(int Limit) : limit(Limit) {
       // Line limit(for ram usage) 0 = unlimited(in theory)
    }
        
    
    SheetReader() {
       // Line limit(for ram usage) 0 = unlimited(in theory)
       // Default value defined above
    }

    template <typename T> // generic read function, calls the correct specific read function based on vectors type
    void readData(const std::string &fileName, std::vector<T> &data, bool debug);
    //void readData(const std::string &fileName, std::vector<T> &data, void (*readFunction)(std::istringstream &, T &), bool debug);

private:
    const int limit = DEFAULTLIMIT;
    // Private member functions for reading specific types of data
    void readLinkUtils(std::istringstream &iss, Linkutils &linkUtilsItem);
    void readTraffic(std::istringstream &iss, Traffic &trafficItem);
    void readPaths(std::istringstream &iss, Paths &pathsItem);
    void readRouters(std::istringstream &iss, Router &routerItem);
    void readLinks(std::istringstream &iss, Link &linkItem);
};

#endif // SHEETREADER_H
