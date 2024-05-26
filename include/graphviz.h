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
#include "mainwindow.h"
using namespace std;

class Graphviz
{
public:
    static void GenerateDotandPNGFile(const string &filename, bool usePreLoad, bool useTraffic, bool mincut, std::optional<std::string> result = nullopt);

private:
    static void writeRouters(ofstream &dotFile, vector<MappedRouter> &routervector);
    static void writeTraffic(std::ofstream &dotFile, const std::vector<AugmentedLink> &linksData, bool usePreLoad, bool PeaksetOnly, std::optional<std::string> result);
    // static void writePaths(ofstream& dotFile, const vector<Paths>& pathsData);
    // static void writeLinkUtils(ofstream& dotFile, const vector<Linkutils>& linkUtilsData);
    static void writeLinks(ofstream &dotFile, const vector<AugmentedLink> &linksData, std::optional<std::string> result);
    static void GenerateImageFromDotFile(string dotFilename);
    static std::string convertDotToPngFilename(const std::string &dotFilename);
    static void InvertDotFile(const std::string &dotFilename);
    static std::string doubleToString(double db);
    static void writeMincut(std::ofstream &dotFile, const std::vector<AugmentedLink> &linksData);
    static std::string getRightColor(const AugmentedLink &link, std::optional<std::string> result, const std::string &normalColor, const std::string &specialColor);
};
#endif // GRAPHVIZ_H