cmake_minimum_required(VERSION 3.14)

if (WIN32)
    project(Network_Simulator LANGUAGES CXX)
elseif(UNIX)
    project(Network_Simulator)
endif()

set(CMAKE_CONFIGURATION_TYPES "Release;RelWithDebInfo" CACHE STRING "" FORCE)

#======================= INCLUSION OF Qt =======================#
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH $ENV{QTDIR})
find_package(Qt6Core REQUIRED)
find_package(Qt6Widgets REQUIRED)

#=================== INCLUSION OF Project Files ====================#
set(FORMS_DIR "${CMAKE_SOURCE_DIR}/forms")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")

include_directories(${FORMS_DIR})
include_directories(${INCLUDE_DIR})
include_directories(${SOURCE_DIR})

file(GLOB_RECURSE PROJECT_SOURCES
    "${FORMS_DIR}/*.ui"
    "${FORMS_DIR}/*.qrc"
    "${INCLUDE_DIR}/*.h"
    "${SOURCE_DIR}/*.cpp"
)

#=================== SETUP EXECTUABLE ====================#
# Enable debug logging on RELWITHDEBINFO configuration
set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS
    $<$<CONFIG:RELWITHDEBINFO>:QT_MESSAGELOGCONTEXT>
)

# Add the forms directory to the AUTOUIC search paths
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_AUTOUIC_SEARCH_PATHS} ${FORMS_DIR})

# Add the executable
if (WIN32) 
    add_executable(Network_Simulator WIN32 ${PROJECT_SOURCES})
elseif(UNIX)
    add_executable(Network_Simulator ${PROJECT_SOURCES})
endif()

# Add the target includes for Network_Simulator 
target_include_directories(Network_Simulator PRIVATE ${FORMS_DIR})
target_include_directories(Network_Simulator PRIVATE ${INCLUDE_DIR})
target_include_directories(Network_Simulator PRIVATE ${SOURCE_DIR})

#===================== LINKING LIBRARIES =======================#
target_link_libraries(Network_Simulator Qt6::Widgets)

#====================TESTING========================#
include(FetchContent)
FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.0.1  # You can specify the version you need
)
FetchContent_MakeAvailable(catch2)

# Test sources (tests)
file(GLOB_RECURSE TEST_SOURCES
    "${CMAKE_SOURCE_DIR}/tests/*.cpp"
)

# Combine project sources and test sources
set(FILE_TO_REMOVE "${CMAKE_SOURCE_DIR}/src/main.cpp")
list(REMOVE_ITEM PROJECT_SOURCES "${FILE_TO_REMOVE}")
list(APPEND ALL_TEST_SOURCES ${PROJECT_SOURCES} ${TEST_SOURCES})

# Add the test executable
add_executable(testing ${ALL_TEST_SOURCES})

# Add the target includes for the test executable

target_include_directories(testing PRIVATE ${FORMS_DIR})
target_include_directories(testing PRIVATE ${INCLUDE_DIR})
target_include_directories(testing PRIVATE ${SOURCE_DIR})
target_include_directories(testing PRIVATE ${CMAKE_SOURCE_DIR}/tests)

# Link Catch2 to the test executable
target_link_libraries(testing PRIVATE Catch2::Catch2WithMain Qt6::Widgets)
