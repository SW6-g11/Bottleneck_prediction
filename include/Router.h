#ifndef ROUTER_H
#define ROUTER_H
#include <string>
using namespace std;
class Router
{
public:
    string id;
    double latitude;
    double longitude;
    string type;

    // Default constructor
    Router() : id(""), latitude(0.0), longitude(0.0), type("") {}

    // Constructor with parameters
    Router(const string &id, double latitude, double longitude, const string &type)
        : id(id), latitude(latitude), longitude(longitude), type(type) {}
};
#endif
