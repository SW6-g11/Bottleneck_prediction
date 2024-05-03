#ifndef GRAPHVIZ_H
#define GRAPHVIZ_H
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Linkutils;
class Traffic;
class Paths;
class Router;
class Link;

class Graphviz {
public:
    static void GenerateGraphViz(const vector<Linkutils>& linkUtilsData, const vector<Traffic>& trafficData, const vector<Paths>& pathsData, const vector<Router>& routersData, const vector<Link>& linksData, const string& filename);
};
#endif;  // GRAPHVIZ_H
