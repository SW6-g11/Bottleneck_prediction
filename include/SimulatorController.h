#ifndef SIMULATORCONTROLLER
#define SIMULATORCONTROLLER

#include <string.h>

#include "graphDataStruct.h"
#include "DinicAlgorithm.h"

class SimulatorController
{
public:
    SimulatorController() = delete;
    static void runDinics(const std::string startLink, const std::string endLink);
    static graphDataStruct &getGraphDataPointer();

    // static DinicAlgorithm &getDinicsInstance(const std::vector<Link> &linksData);

private:
    static graphDataStruct graphData;
    static DinicAlgorithm dinicsInstance;
};
/*
class SimulatorController
{
public:
    static SimulatorController &getInstance()
    {
        static SimulatorController instance; // Guaranteed to be destroyed.
                                             // Instantiated on first use.
        return instance;
    }
    SimulatorController(SimulatorController const &) = delete;
    void operator=(SimulatorController const &) = delete;

private:
    SimulatorController() {}
};
*/

#endif