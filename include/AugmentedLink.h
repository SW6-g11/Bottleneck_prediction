#ifndef AUGMENTEDLINK_H
#define AUGMENTEDLINK_H
#include <vector>
#include <string>
#include "Link.h"
#include <iostream>
using namespace std;

class AugmentedLink : public Link
{
public:
    AugmentedLink(string &linkStart, string &linkEnd, double capacity) : Link(linkStart, linkEnd, capacity){};
    AugmentedLink() : Link(){};
    int start_;
    int end_;
    double preload = 0.0;
    double flow = 0;
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

    int getRemainingCapacity(int from, bool usePreLoad, bool isCalculatingMincut) const
    { // Gets the capacity of the edge if the originating vertex is `from`
        // std::cout << "preload? " << usePreLoad << " capacity; " << capacity << " preload value: " << preload << " return: " << (preload ? capacity - preload - flow : capacity - flow) << std::endl;
        if (isCalculatingMincut)
        {
            return 1 - flow;
        }
        if (from == start_)
        {
            // std::cout << "From " << from << "=" << start_ << " start" << std::endl;
            return (preload ? capacity - preload - flow : capacity - flow);
        }
        // std::cout << "From " << from << "!=" << start_ << " start" << std::endl;
        return (preload ? flow - preload : flow);
    }
    std::string toString() const
    {
        return linkStart + "" + linkEnd + " indexes: " + std::to_string(start_) + "," + std::to_string(end_) + ", capacity: " + std::to_string(capacity) + ", flow: " + std::to_string(flow);
    }
    std::string to_string() const
    {
        return "(" + linkStart + "," + linkEnd + "),i:(" + std::to_string(start_) + "," + std::to_string(end_) + "))";
    }
};
#endif