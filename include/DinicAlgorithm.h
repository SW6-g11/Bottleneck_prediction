#ifndef DINICALGORITHM_H
#define DINICALGORITHM_H

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <unordered_map>
#include "Link.h"
#include "MappedRouter.h"
#include "AugmentedLink.h"

class DinicAlgorithm
{
private:
    bool adjecentMapIsPopulated = false;
    std::unordered_map<std::string, std::vector<Link>> AdjecentMap;
    std::unordered_map<std::string, int> level;
    std::unordered_map<std::string, int> NextEdgePointer; // Next edge (link) to be visited

    bool bfs(const std::string &source, const std::string &sink);
    double dfs(const std::string &u, const std::string &sink, double minCapacity);

    vector<MappedRouter> nodes_;
    deque<AugmentedLink> arcs_;

    void applyindices(vector<AugmentedLink> &links);
    bool getIndexOfSourceAndSink(int &indexSource, int &indexSink, std::string source, std::string sink);
    template <typename T>
    void printArr(const std::vector<T> &arr, const std::string name);
    // Specialization for when T is int
    void printArr(const std::vector<int> &arr, const std::string name);

public:
    DinicAlgorithm();
    void PopulateAdjecencymap(vector<AugmentedLink> &links, vector<MappedRouter> &routers, bool overwrite);
    void populateDinics(vector<AugmentedLink> &links, vector<MappedRouter> &routers, bool overwrite);
    int compute_flow(std::string source, std::string sink);
    // double findMaxFlow(const std::string &source, const std::string &sink);
    // int compute_flow(int source_i, int sink_i);
};

#endif // DINICALGORITHM_H