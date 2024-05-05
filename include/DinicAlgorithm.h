#ifndef DINICALGORITHM_H
#define DINICALGORITHM_H

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <unordered_map>
#include "link.h" 

class DinicAlgorithm {
private:
    std::unordered_map<std::string, std::vector<Link>> AdjecentMap;
    std::unordered_map<std::string, int> level;
    std::unordered_map<std::string, int> NextEdgePointer;

    bool bfs(const std::string& source, const std::string& sink);
    double dfs(const std::string& u, const std::string& sink, double minCapacity);

public:
    DinicAlgorithm(const std::vector<Link>& links);
    double findMaxFlow(const std::string& source, const std::string& sink);
};

#endif // DINICALGORITHM_H