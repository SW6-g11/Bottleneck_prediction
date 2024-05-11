#include <string.h>
#include "Path.h"
#include "graphDataStruct.h"
#include "Linkutils.h"
#include <unordered_map>

class Networkmanipulator
{
public:
    static void findPeakUtilValues(int amountofBottleneckLinks, vector<std::pair<std::string, Linkutils>> &PeakUtilValues, graphDataStruct &graphData);
    static vector<Paths> findLinksInPaths(std::vector<std::pair<std::string, Linkutils>> peakset, int amountofBottleneckLinks, graphDataStruct &graphData);
    static void reducelinkvector(std::vector<std::pair<std::string, Linkutils>> &vec, int Y);

    template <typename T>
    static void reduceVector(vector<T> &vector, int Y)
    {
        if (Y >= vector.size())
        {
            // Nothing to do if Y is greater than or equal to the size of the vector
            return;
        }

        vector.erase(vector.begin() + Y, vector.end());
    }

private:
    // void reducePathvector(std::unordered_map<std::string, Paths> &vec, int Y);
    static bool alphanumericCompare(const std::string &a, const std::string &b);
    static bool alphanumericCompareDecorator(const Paths a, const Paths b);
    static std::unordered_map<std::string, Linkutils> findPeaks(graphDataStruct &graphData);

    // vector<T &> replaceByFingerPrint(std::string (SimulatorController::makeFingerPrintFunction)(T), T linkObj, vector<T>arr);
    static std::string makeFingerPrint(Linkutils LinkUtils);
    static std::string makeFingerPrint(Link link);

    static bool comparePeakUtilValues(const std::pair<std::string, Linkutils> &a, const std::pair<std::string, Linkutils> &b);
    static bool comparePathLength(const Paths &a, const Paths &b);
    // void AugmentNetworkbyTimeStamp(string timestamp, vector<Linkutils> &Linkutildata, vector<Linkutils> &AugmentedLinks);

    static string PathCorrector(Paths chaoticpath);
};
