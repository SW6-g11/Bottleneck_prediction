cmake_minimum_required(VERSION 3.5)

project(Network_Simulator VERSION 0.1)

#set to True if QT should be used
set("use_qt" "FALSE")
set("CMAKE_GENERATOR" "Ninja")

if(${use_qt})
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
# find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        NetworkCode/main.cpp
        # NetworkCode/mainwindow.cpp
        # NetworkCode/mainwindow.h
        # NetworkCode/mainwindow.ui

        # graphLoader.cpp
        # graphLoader.h
        NetworkCode/SheetToGraphConverter/Graphmaker.cpp
        NetworkCode/SheetToGraphConverter/Graphmaker.h
        NetworkCode/SheetToGraphConverter/Inputverifyer.h

        NetworkCode/SheetToGraphConverter/Link.h

        NetworkCode/SheetToGraphConverter/Linkutils.h

        NetworkCode/SheetToGraphConverter/path.h

        NetworkCode/SheetToGraphConverter/router.h
        NetworkCode/SheetToGraphConverter/SheetReader.cpp
        NetworkCode/SheetToGraphConverter/SheetReader.h

        NetworkCode/SheetToGraphConverter/Traffic.h


)

if(${use_qt})
    if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
        qt_add_executable(NetworkCode
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
        )
    # Define target properties for Android with Qt 6 as:
    #    set_property(TARGET NetworkCode APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
    #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
    else()
        if(ANDROID)
            add_library(NetworkCode SHARED
                ${PROJECT_SOURCES}
            )
    # Define properties for Android with Qt 5 after find_package() calls as:
    #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
        else()
            add_executable(NetworkCode
                ${PROJECT_SOURCES}
            )
        endif()
    endif()

    target_link_libraries(NetworkCode PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

    # Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
    # If you are developing for iOS or macOS you should consider setting an
    # explicit, fixed bundle identifier manually though.
    if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.NetworkCode)
    endif()
    set_target_properties(NetworkCode PROPERTIES
        ${BUNDLE_ID_OPTION}
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
    )

    include(GNUInstallDirs)
    install(TARGETS NetworkCode
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

    if(QT_VERSION_MAJOR EQUAL 6)
        qt_finalize_executable(NetworkCode)
    endif()
else()
    message(STATUS "Current source directory: ${CMAKE_SOURCE_DIR}")
    message(STATUS "Current binary directory: ${CMAKE_INSTALL_BINDIR}")
    # set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
    add_executable(NetworkCode ${PROJECT_SOURCES})
    include(GNUInstallDirs)
    install(TARGETS NetworkCode
        BUNDLE DESTINATION ./build
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/build
        RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/build
    )
endif()