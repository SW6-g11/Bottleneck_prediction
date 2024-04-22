#include "path.h"

using namespace std;
class Paths
{
public:
    string timestamp;
    string origin;
    string destination;
    vector<string> path; // Changed to a pointer

    // Default constructor
    Paths() : timestamp(""), origin(""), destination(""), path() {}

    // Constructor with parameters
    Paths(const string &timestamp, const string &origin, const string &destination, vector<string> path)
        : timestamp(timestamp), origin(origin), destination(destination), path(path) {}

    // Destructor
    ~Paths()
    {
        // delete path;
    }
};
