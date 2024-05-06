#ifndef SHEETREADER_H
#define SHEETREADER_H
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo>
#include <vector>
#include "inputverifyer.h"
#include "link.h"
#include "linkutils.h"
#include "path.h"
#include "router.h"
#include "traffic.h"
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
  // overloading constructor (have one use the other) gives us an optional input
  // "limit"
  SheetReader(int Limit) : limit(Limit) {
    // Line limit(for ram usage) 0 = unlimited(in theory)
  }

  SheetReader() {
    // Line limit(for ram usage) 0 = unlimited(in theory)
    // Default value defined above
  }

  template <typename T>
  void readData(const string& fileName, vector<T>& data, bool debug) {
    // cout << "Inside function 1 ";
    if (debug)
      cout << "Inside function 1 ";
    ifstream file(fileName);
    if (debug)
      cout << "2 ";
    if (!file) {
      cout << "Error ";
      cerr << "Error: Unable to open file " << fileName << endl;
      return;
    }
    if (debug)
      cout << "3 ";
    const int bufferSize = 1024;  // Adjust buffer size as needed
    if (debug)
      cout << "4 ";
    char buffer[bufferSize];
    if (debug)
      cout << "5 ";
    int count = 0;
    if (debug)
      cout << "6 ";
    int i = 0;
    cout << "the filename is : " + fileName + " : " << endl;
    while (file.getline(buffer, bufferSize) && i < limit) {
      i++;
      if (debug) {
        cout << "reading line " + to_string(count) + fileName + ": ";
      }
    //   cout << "reading line " + to_string(count) + fileName + ": ";
      istringstream iss(buffer);
      T item;
      readType(iss, item);
      data.push_back(item);
      count++;
    }
  }
  // void readData(const std::string &fileName, std::vector<T> &data, void
  // (*readFunction)(std::istringstream &, T &), bool debug);

 private:
  const int limit = DEFAULTLIMIT;
  // Private member functions for reading specific types of data
  // void readLinkUtils(istringstream &iss, Linkutils &linkUtilsItem);
  // void readTraffic(istringstream &iss, Traffic &trafficItem);
  // void readPaths(istringstream &iss, Paths &pathsItem);
  // void readRouters(istringstream &iss, Router &routerItem);
  // void readLinks(istringstream &iss, Link &linkItem);
  template <typename T>
  void readType(istringstream& iss, T& typeItem);
};

#endif  // SHEEHTREADER_