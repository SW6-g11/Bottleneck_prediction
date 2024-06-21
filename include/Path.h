#ifndef PATH_H
#define PATH_H
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Paths
{
public:
    string timestamp;
    int origin;
    int destination;
    vector<int> path; // Changed to a pointer
    int pathLength;

    // Default constructor
    // Paths() : timestamp(-1), origin(-1), destination(-1), path([]) {}

    // Constructor with parameters
    Paths(const string &timestamp, const int &origin, const int &destination, vector<int> path)
        : timestamp(timestamp), origin(origin), destination(destination), path(path)
    {

        pathLength = path.size() + 2;
        // fingerprint = this->to_string();
    }
    void applyChanges()
    {
        pathLength = path.size() + 2;
        // fingerprint = this->to_string();
    }
    // Destructor
    ~Paths()
    {
        // delete path;
    }
    string to_string() const
    {
        std::string result = std::to_string(origin) + ",";
        for (int i = 0; i < path.size(); i++)
        {
            result += path[i] + ",";
        }
        return result + std::to_string(destination);
    }
    /*
    bool operator==(const Paths &other) const
    {
        return this->fingerprint == other.fingerprint;
    }
    */
};
#endif // PATH_H