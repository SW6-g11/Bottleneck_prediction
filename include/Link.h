#ifndef LINK_H
#define LINK_H
#include <string>
using namespace std;

class Link
{
public:
    int linkStart;
    int linkEnd;
    double capacity;

    // Default constructor
    Link() : linkStart(-1), linkEnd(-1), capacity(0.0) {}

    // Constructor with parameters
    Link(int linkStart, int linkEnd, double capacity)
        : linkStart(linkStart), linkEnd(linkEnd), capacity(capacity) {}
};
#endif // LINK_H