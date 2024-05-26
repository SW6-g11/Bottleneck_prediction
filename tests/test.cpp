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

    //Test empty graphData
    REQUIRE(graphData.linkUtilsData.size() == 0);
    REQUIRE(graphData.trafficData.size() == 0);
    REQUIRE(graphData.pathsData.size() == 0);
    REQUIRE(graphData.MappedRouterVector.size() == 0);
    REQUIRE(graphData.Augmentedlinks.size() == 0);

    // Read data
    Readmaster.readData(path + "/link-util-day" + to_string(day) + ".csv", graphData.linkUtilsData, false);
    Readmaster.readData(path + "/flow-traffic-day" + to_string(day) + ".csv", graphData.trafficData, false);
    Readmaster.readData(path + "/flow-paths-day" + to_string(day) + ".csv", graphData.pathsData, false);
    Readmaster.readData(path + "/routers.csv", graphData.MappedRouterVector, true);
    Readmaster.readData(path + "/links.csv", graphData.Augmentedlinks, true);

    //Test readData size
    REQUIRE(graphData.linkUtilsData.size() == 71);
    REQUIRE(graphData.trafficData.size() == 26);
    REQUIRE(graphData.pathsData.size() == 116);
    REQUIRE(graphData.MappedRouterVector.size() == 9);
    REQUIRE(graphData.Augmentedlinks.size() == 24);

    //Test readData content for linkUtilsData (first and last)
    REQUIRE(graphData.linkUtilsData[0].linkStart == "R1");
    REQUIRE(graphData.linkUtilsData[0].linkEnd == "R2");
    REQUIRE(graphData.linkUtilsData[70].linkStart == "R10");
    REQUIRE(graphData.linkUtilsData[70].linkEnd == "R8");

    //Test readData content for trafficData (first and last)
    REQUIRE(graphData.trafficData[0].origin == "R4291");
    REQUIRE(graphData.trafficData[0].destination == "R4291");
    REQUIRE(graphData.trafficData[25].origin == "R3459");
    REQUIRE(graphData.trafficData[25].destination == "R1538");

    //Test readData content for pathsData (first and last)
    REQUIRE(graphData.pathsData[0].origin == "R1");
    REQUIRE(graphData.pathsData[0].destination == "R2");
    REQUIRE(graphData.pathsData[115].origin == "R8");
    REQUIRE(graphData.pathsData[115].destination == "R4");


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

    //Manual reset
    SimulatorController::resetDinics();

    

    //Test Algorithm 4
    auto result3 = SimulatorController::minCut("R1", "R4", true);
    std::cout << "rsult3.size_ " << result3.size() << std::endl;  
    std::stringstream ss3;
    for (const auto &res : result3) {
        ss3 << res.first << " - " << res.second << "\n";
    }
    std::string resultString3 = ss3.str();
    std::cout << "resultString3: " << resultString3 << std::endl;
    //REQUIRE(resultString3 == "R1 - R2\nR1 - R4");
}

