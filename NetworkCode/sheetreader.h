#ifndef SHEETREADER_H
#define SHEETREADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <filesystem>
#include "path.h"
#include "link.h"
#include "router.h"
#include "inputverifyer.h"
#include "linkutils.h"

class Linkutils;
class Traffic;
class Paths;
class Router;
class Link;

template <typename T>
class SheetReader {
public:
    // Constructor(s), destructor, and any other public members

    void readData(const std::string &fileName, std::vector<T> &data, void (*readFunction)(std::istringstream &, T &), bool debug);

private:
    // Private member functions for reading specific types of data
    void readLinkUtils(std::istringstream &iss, Linkutils &linkUtilsItem);
    void readTraffic(std::istringstream &iss, Traffic &trafficItem);
    void readPaths(std::istringstream &iss, Paths &pathsItem);
    void readRouters(std::istringstream &iss, Router &routerItem);
    void readLinks(std::istringstream &iss, Link &linkItem);
};

#endif // SHEETREADER_H
