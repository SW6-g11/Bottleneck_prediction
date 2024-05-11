#ifndef AUGMENTEDLINK_H
#define AUGMENTEDLINK_H
#include <vector>
#include <string>
#include "Link.h"
using namespace std;

class AugmentedLink : public Link
{
public:
    AugmentedLink(string &linkStart, string &linkEnd, double capacity) : Link(linkStart, linkEnd, capacity){};
    AugmentedLink() : Link(){};
    int start_;
    int end_;
    std::string start;
    std::string end;
    double flow;
    double capacity;
    int get_dest(int from) const
    { // Return the destination node if we were to traverse the arc from node `from`
        if (from == start_)
        {
            return end_;
        }
        else
        {
            return start_;
        }
    }

    void addFlow(int from, double to_add)
    { // Adds flow from originating vertex `from`
        if (from == start_)
        {
            flow += to_add;
        }
        else
        {
            flow -= to_add;
        }
    }

    int getRemainingCapacity(int from) const
    { // Gets the capacity of the edge if the originating vertex is `from`
        if (from == start_)
        {
            return capacity - flow;
        }
        else
        {
            return flow;
        }
    }
};
#endif