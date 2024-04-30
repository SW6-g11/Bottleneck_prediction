#ifndef LINK_H
#define LINK_H
#include <string>
using namespace std;

class Link
{
public:
    string linkStart;
    string linkEnd;
    double capacity;

    // Default constructor
    Link() : linkStart(""), linkEnd(""), capacity(0.0) {}

    // Constructor with parameters
    Link(string &linkStart, string &linkEnd, double capacity)
        : linkStart(linkStart), linkEnd(linkEnd), capacity(capacity) {}
};
#endif // LINK_H