#ifndef TRAFFIC_H
#define TRAFFIC_H
using namespace std;
class Traffic
{
public:
    string timestamp;
    string origin;
    string destination;
    double avgTraffic;

    // Default constructor
    Traffic() : timestamp(""), origin(""), destination(""), avgTraffic(0.0) {}

    // Constructor with parameters
    Traffic(const string &timestamp, const string &origin, const string &destination, double avgTraffic)
        : timestamp(timestamp), origin(origin), destination(destination), avgTraffic(avgTraffic) {}
};
#endif // TRAFFIC_H 