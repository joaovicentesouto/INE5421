################################################################################
# This is the CMakeLists file for the:
#
#   formal_languages GUI
#
# Its main goals are:
#   - Create an graphic user interface.
#
################################################################################

add_subdirectory(model)

################################################################################
# Set flags
################################################################################

#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTOUIC ON)
#set(CMAKE_INCLUDE_CURRENT_DIR ON)

################################################################################
# Fetch files
################################################################################

# Fetch .cpp files for executable creation
#file(GLOB_RECURSE formal_languages_gui_source
#    "*.cpp"
#)

# Fetch .ui files for executable creation
#file(GLOB_RECURSE formal_languages_gui_userinterface
#    "*.ui"
#)

################################################################################
# GUI executable
################################################################################

# Add gui executable
add_executable( formal_languages_gui "./main.cpp")

# Add executable dependencies
target_link_libraries(formal_languages_gui PUBLIC
    PRIVATE formal_languages_model_static
)
#    PRIVATE Qt5::Widgets
#)
