#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "SimulatorController.h"
#include <QApplication>
#include "mainwindow.h"
#include "DinicAlgorithm.h"
#include "graphmaker.h"
#include "Sheetreader.h"

TEST_CASE("Algorithm 1 result", "[Alg1test]") {
    Graphmaker graphOne;
    std::string path = "/home/anders/Bottleneck_prediction/data/sampleSet";
    int day = 1;
    int limit = 0;
    SheetReader Readmaster(limit);
    graphDataStruct &graphData = SimulatorController::getGraphDataPointer();
    Readmaster.readData(path + "/link-util-day" + to_string(day) + ".csv", graphData.linkUtilsData, false);
    Readmaster.readData(path + "/flow-traffic-day" + to_string(day) + ".csv", graphData.trafficData, false);
    Readmaster.readData(path + "/flow-paths-day" + to_string(day) + ".csv", graphData.pathsData, false);
    Readmaster.readData(path + "/routers.csv", graphData.MappedRouterVector, true);
    Readmaster.readData(path + "/links.csv", graphData.Augmentedlinks, true);
                
    //Test Algorithm 1
    REQUIRE(SimulatorController::runDinics("R1", "R4", false, false) == 30);

    //Test Algorithm 2
    auto result = SimulatorController::DinicsOnBottlenecksNoAugmentedNetork(5, 1, false);
    std::stringstream ss;
    for (const auto &res : result) {
        ss << res.first << res.second;
    }
    std::string resultString = ss.str();
    std::cout << "resultString: " << resultString << std::endl;
    REQUIRE(resultString == "R1,R2,R4,R3,R7,R6,R86");

    //Test Algorithm 3
    auto result2 = SimulatorController::DinicsOnBottlenecksNoAugmentedNetork(5, 1, true);
    std::stringstream ss2;
    for (const auto &res : result2) {
        ss2 << res.first << res.second;
    }
    std::string resultString2 = ss2.str();
    std::cout << "resultString2: " << resultString2 << std::endl;
    REQUIRE(resultString2 == "R1,R2,R4,R3,R7,R6,R85");

    //Test Algorithm 4
    auto result3 = SimulatorController::minCut("R1", "R4", false);
    std::stringstream ss3;
    for (const auto &res : result3) {
        ss3 << res.first << res.second;
    }
    std::string resultString3 = ss3.str();
    std::cout << "resultString3: " << resultString3 << std::endl;
    REQUIRE(resultString3 == "R1 - R2\nR1 - R4");
}

