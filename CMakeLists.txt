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
set(GRAPHVIZ_DIR "${CMAKE_SOURCE_DIR}/Graphviz")

include_directories(${FORMS_DIR})
include_directories(${INCLUDE_DIR})
include_directories(${SOURCE_DIR})
include_directories(${GRAPHVIZ_DIR})

file(GLOB_RECURSE SOURCES
    "${FORMS_DIR}/*.ui"
    "${FORMS_DIR}/*.qrc"
    "${INCLUDE_DIR}/*.h"
    "${SOURCE_DIR}/*.cpp"
    "${GRAPHVIZ_DIR}/*.h"
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
    add_executable(Network_Simulator WIN32 ${SOURCES})
elseif(UNIX)
    add_executable(Network_Simulator ${SOURCES})
endif()

# Add the target includes for Network_Simulator 
target_include_directories(Network_Simulator PRIVATE ${GRAPHVIZ_DIR})
target_include_directories(Network_Simulator PRIVATE ${FORMS_DIR})
target_include_directories(Network_Simulator PRIVATE ${INCLUDE_DIR})
target_include_directories(Network_Simulator PRIVATE ${SOURCE_DIR})

#===================== LINKING LIBRARIES =======================#
target_link_libraries(Network_Simulator Qt6::Widgets)