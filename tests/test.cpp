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
                
    REQUIRE(1 == 1);
    REQUIRE(SimulatorController::runDinics("R1", "R4", false, false) == 30);
    REQUIRE(SimulatorController::runDinics("R1", "R4", false, true) == 30);
}

