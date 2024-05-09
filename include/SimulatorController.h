#ifndef SIMULATORCONTROLLER
#define SIMULATORCONTROLLER

#include <string.h>
#include "path.h"
#include "graphDataStruct.h"
#include "DinicAlgorithm.h"

class SimulatorController
{
public:
    SimulatorController() = delete;

    static void runDinics(const std::string startLink, const std::string endLink);

    static graphDataStruct &getGraphDataPointer();

    template <typename T>
    static vector<T> replaceByFingerPrint(std::string(makeFingerPrintFunction)(T), T linkObj, vector<T> arr)
    // vector<T> replaceByFingerPrint(std::string (makeFingerPrintFunction)(T))
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

    static void DinicsOnBottlenecksNoAugmentedNetork(int amountPUV, int amountPaths);

private:
    static graphDataStruct graphData;
    static DinicAlgorithm dinicsInstance;
};

#endif