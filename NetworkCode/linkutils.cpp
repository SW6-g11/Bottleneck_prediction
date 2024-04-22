#include "linkutils.h"

using namespace std;

class Linkutils
{
public:
    string timestamp;
    string linkStart;
    string linkEnd;
    double avgUtilization;

    // Default constructor
    Linkutils() : timestamp(""), linkStart(""), linkEnd(""), avgUtilization(0.0) {}

    // Constructor with parameters
    Linkutils(const string &timestamp, const string &linkStart, const string &linkEnd, double avgUtilization)
        : timestamp(timestamp), linkStart(linkStart), linkEnd(linkEnd), avgUtilization(avgUtilization) {}
};
