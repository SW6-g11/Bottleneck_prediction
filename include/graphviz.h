#ifndef GRAPHVIZ_H
#define GRAPHVIZ_H
#include <string>
#include <vector>
#include <iostream>
#include "graphmaker.h"
#include "Link.h"
#include "Linkutils.h"
#include "Path.h"
#include "Router.h"
#include "Sheetreader.h"
#include "Traffic.h"
#include <iostream>
#include <fstream>
#include <mainwindow.h>
using namespace std;

class Graphviz
{
public:
    static void GenerateGraphViz(const string& filename, bool usepreload);

private:
    static void writeRouters(ofstream& dotFile, vector<MappedRouter>& routervector);
    static void writeTraffic(ofstream& dotFile, const vector<AugmentedLink>& linksData, bool usepreload);
    // static void writePaths(ofstream& dotFile, const vector<Paths>& pathsData);
    // static void writeLinkUtils(ofstream& dotFile, const vector<Linkutils>& linkUtilsData);
    static void writeLinks(ofstream& dotFile, const vector<AugmentedLink>& linksData);
    static void  GenerateImageFromDotFile(string dotFilename);
    static std::string convertDotToPngFilename(const std::string& dotFilename);
    static void InvertDotFile(const std::string& dotFilename);

};
#endif // GRAPHVIZ_H