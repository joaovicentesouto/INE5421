################################################################################
# This is the main CMakeLists file for the pratical work for INE5421.
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
cmake_minimum_required(VERSION 3.5.2)

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

# Find Boost
find_package(Boost 1.59 REQUIRED)

# Find GUI Dependencies
IF(GUI)
    # Find Qt5
    find_package(Qt5 REQUIRED COMPONENTS Widgets)
ENDIF(GUI)


################################################################################
# Project logic 
################################################################################

# Add subdirectories
add_subdirectory(src)
add_subdirectory(tests)
