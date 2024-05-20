#ifndef GRAPHVIZ_H
#define GRAPHVIZ_H
#include <string>
#include <vector>
#include <iostream>
#include "graphmaker.h"
#include "link.h"
#include "linkutils.h"
#include "path.h"
#include "router.h"
#include "sheetreader.h"
#include "traffic.h"
#include <iostream>
#include <fstream>
#include <mainwindow.h>
using namespace std;

class Graphviz {
public:
    static void GenerateGraphViz(const string& filename);

private:
    static void writeRouters(ofstream& dotFile, const vector<Router>& routersData);
    static void writeTraffic(ofstream& dotFile, const vector<Traffic>& trafficData);
    static void writePaths(ofstream& dotFile, const vector<Paths>& pathsData);
    static void writeLinkUtils(ofstream& dotFile, const vector<Linkutils>& linkUtilsData);
    static void writeLinks(ofstream& dotFile, const vector<Link>& linksData);
};
#endif;  // GRAPHVIZ_H