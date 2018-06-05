################################################################################
# This is the main CMakeLists file for the pratical work for INE5421.
#
# Authors: João Vicente Souto e Bruno Izaias Bonotto
#
# Its main goals are:
#   - Set up global variables.
#   - Configure dependencies (find_package).
#   - Add subdirectories.
#
################################################################################

################################################################################
# Set up global variables
################################################################################

# Set up minimal cmake version
cmake_minimum_required(VERSION 3.5.1)

# Set project name
project(formal_languages)

# Set project version
set(formal_languages_VERSION 0.1)

# Set c++14 globally
set(CMAKE_CXX_STANDARD 14)

# Set formal_languages source dir
set(formal_languages_source_dir ${PROJECT_SOURCE_DIR})

# Build graphic user interface of ophidian
OPTION(GUI OFF)

################################################################################
# Handle raquirements
################################################################################

# Find GUI Dependencies
IF(GUI)
    if (APPLE)
        message("-- Qt5 on Mac: You need the QT5 path installed by Qt creator if you want to compile without the using Qt Creator.")
        set(QT5_PATH $ENV{HOME}/Qt/5.10.1/clang_64/ CACHE PATH "Path to Qt5")
        set(QT5_MODULE_PATH ${QT5_PATH}/lib/cmake)
        set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${QT5_MODULE_PATH})
    endif(APPLE)

    if (UNIX AND NOT APPLE)
        message("-- Qt5 on Mac: You need the QT5 path installed by Qt creator if you want to compile without the using Qt Creator.")
        set(QT5_PATH $ENV{HOME}/Qt/5.9.1/gcc_64/ CACHE PATH "Path to Qt5")
        set(QT5_MODULE_PATH ${QT5_PATH}/lib/cmake)
        set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${QT5_MODULE_PATH})
    endif(UNIX AND NOT APPLE)

    # Find Qt5
    find_package(Qt5 REQUIRED COMPONENTS Widgets)
ENDIF(GUI)

################################################################################
# Project logic 
################################################################################

# Add subdirectories
add_subdirectory(formal_languages)
add_subdirectory(tests)

IF(GUI)
    add_subdirectory(gui)
ENDIF(GUI)
