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
file(GLOB_RECURSE context_free_languages_gui_source
    "*.cpp"
)

# Fetch .ui files for executable creation
file(GLOB_RECURSE context_free_languages_gui_userinterface
    "*.ui"
)

################################################################################
# GUI executable
################################################################################

# Add gui executable
add_executable( context_free_languages_gui MACOSX_BUNDLE ${context_free_languages_gui_source} ${context_free_languages_gui_userinterface} )

# Add executable dependencies
target_link_libraries(context_free_languages_gui PUBLIC
    PRIVATE Qt5::Widgets
    PRIVATE context_free_languages_components
    PRIVATE context_free_languages_devices
    PRIVATE context_free_languages_parsers
)
#    PRIVATE Qt5::Widgets
#)
