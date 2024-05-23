#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "SimulatorController.h"
#include <QApplication>
#include "mainwindow.h"
#include "DinicAlgorithm.h"

TEST_CASE("Factorial of 0 is 1 (basic:)", "[single-file]") {
    
    REQUIRE(1 == 1);
    REQUIRE(SimulatorController::runDinics("R1", "R4", false, false) == 30);
    REQUIRE(SimulatorController::runDinics("R1", "R4", false, false) == 20);
}

TEST_CASE("Factorials of 1 and higher are computed (basic:)", "[single-file]") {
}

