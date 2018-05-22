################################################################################
# This is the CMakeLists file for the:
#
#   formal_languages GUI
#
# Its main goals are:
#   - Create an graphic user interface.
#
################################################################################

################################################################################
# Set flags
################################################################################

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

################################################################################
# Fetch files
################################################################################

# Fetch .cpp files for executable creation
file(GLOB_RECURSE formal_languages_gui_source
    "*.cpp"
)

# Fetch .ui files for executable creation
file(GLOB_RECURSE formal_languages_gui_userinterface
    "*.ui"
)

################################################################################
# GUI executable
################################################################################

# Add gui executable
add_executable( formal_languages_gui ${formal_languages_gui_source} ${formal_languages_gui_userinterface} )

# Add executable dependencies
target_link_libraries(formal_languages_gui PUBLIC
    PRIVATE Qt5::Widgets
    PRIVATE formal_languages_components
    PRIVATE formal_languages_devices
    PRIVATE formal_languages_parsers
    PRIVATE formal_languages_manipulators
)
#    PRIVATE Qt5::Widgets
#)
