#ifndef path_H
#define path_H
#include <string>
using namespace std;
// Include any necessary libraries or headers

// Define any necessary classes or structs

// Declare any function prototypes
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
#endif // path_H