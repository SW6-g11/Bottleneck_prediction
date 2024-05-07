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

    static std::unordered_map<std::string, Linkutils> findPeaks();

    static void findPeakUtilValues(int amountofPUVs);

    // vector<T &> replaceByFingerPrint(std::string (SimulatorController::*makeFingerPrintFunction)(T), T linkObj, vector<T> *arr);
    static std::string makeFingerPrint(Linkutils LinkUtils);
    static std::string makeFingerPrint(Link link);

    template <typename T>
    vector<T> replaceByFingerPrint(std::string (*makeFingerPrintFunction)(T), T linkObj, vector<T> arr)
    // vector<T> replaceByFingerPrint(std::string (*makeFingerPrintFunction)(T))
    {
        std::string target = makeFingerPrintFunction(linkObj);
        vector<T> result;
        for (int i = 0; i < arr.size(); i++)
        {
            std::string a = makeFingerPrintFunction(arr[i]);
            if (a == target)
            {
                result.push_back(arr[i]);
            }
        }
        return result;
    }

private:
    static graphDataStruct graphData;
    static DinicAlgorithm dinicsInstance;
};

#endif