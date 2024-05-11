#ifndef AUGMENTEDNETWORKSTRUCT
#define AUGMENTEDNETWORKSTRUCT
#include <vector>
using namespace std;
#include <string>
#include "router.h"
#include "augmentedlinkstruct.h"
#include <deque>
#include <functional>
#include "MappedRouter.h"

struct AugmentedFlowNetwork
{
    std::vector<MappedRouter> routervector;
    std::deque<AugmentedLink> AugmentedlinksQ;
    void add_Router(MappedRouter router)
    {
        routervector.push_back(router);
    }

    // void add_arc(int start, int end, int capacity, int flow = 0)
    // {
    //     AugmentedlinksQ.push_back({start, end, flow, capacity});
    //     nodes_[start].connected_arcs_.push_back(&arcs_.back());
    //     nodes_[end].connected_arcs_.push_back(&arcs_.back());
    // }
};
#endif