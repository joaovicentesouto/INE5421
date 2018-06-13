################################################################################
# This is the CMakeLists file for the:
#
#   namespace context_free_languages::parser
#
# Its main goals are:
#   - Fetch library files.
#   - Add target.
#       `- Set target_include_path.
#       `- Set target_link_libraries.
#       `- Set target_compiler_options.
#   - Define installation parameters.
#       `- Install targets.
#       `- Install headers.
#
################################################################################

################################################################################
# Set variables
################################################################################

# Set the include path for installed target
set(context_free_languages_manipulators_install_include_dir
    ${formal_languages_install_include_dir}/context_free_languages/parser
)

################################################################################
# Fetch files
################################################################################

# Fetch .ccp files for library creation
file(GLOB context_free_languages_manipulators_source
    "*.cpp"
)

# Fetch .h files for library creation
file(GLOB context_free_languages_manipulators_headers
    "*.h"
)

################################################################################
# Library target
################################################################################

# Add library target
add_library(context_free_languages_manipulators SHARED ${context_free_languages_manipulators_source})

# Set shared library version, this will make cmake create a link
set_target_properties(context_free_languages_manipulators PROPERTIES
    VERSION ${formal_languages_VERSION}
    SOVERSION ${formal_languages_VERSION}
)

# Tell cmake target's dependencies
target_link_libraries(context_free_languages_manipulators
   PRIVATE context_free_languages_devices
)

# Tell cmake the path to look for include files for this target
# This is transitive, so any targets linked with this one will
# search for headers in the respective paths
target_include_directories(context_free_languages_manipulators PUBLIC
    $<BUILD_INTERFACE:${formal_languages_source_dir}>
    $<INSTALL_INTERFACE:include>
)

# Add library target
#add_library(context_free_languages_manipulators_static STATIC ${context_free_languages_manipulators_source})

# Tell cmake target's dependencies
#target_link_libraries(context_free_languages_manipulators_static
#)

# Tell cmake the path to look for include files for this target
# This is transitive, so any targets linked with this one will
# search for headers in the respective paths
#target_include_directories(context_free_languages_manipulators_static PUBLIC
#    $<BUILD_INTERFACE:${context_free_languages_source_dir}>
#    $<INSTALL_INTERFACE:include>
#)
