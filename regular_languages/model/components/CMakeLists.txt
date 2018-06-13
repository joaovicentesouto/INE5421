################################################################################
# This is the CMakeLists file for the:
#
#   namespace regular_languages::regular_devices
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
set(regular_languages_components_install_include_dir
    ${formal_languages_install_include_dir}/regular_languages/devices
)

################################################################################
# Fetch files
################################################################################

# Fetch .ccp files for library creation
file(GLOB regular_languages_components_source
    "*.cpp"
)

# Fetch .h files for library creation
file(GLOB regular_languages_components_headers
    "*.h"
)

################################################################################
# Library target
################################################################################

# Add library target
add_library(regular_languages_components SHARED ${regular_languages_components_source})

# Set shared library version, this will make cmake create a link
set_target_properties(regular_languages_components PROPERTIES
    VERSION ${formal_languages_VERSION}
    SOVERSION ${formal_languages_VERSION}
)

# Tell cmake target's dependencies
#target_link_libraries(regular_languages_components
#    PRIVATE 
#)

# Tell cmake the path to look for include files for this target
# This is transitive, so any targets linked with this one will
# search for headers in the respective paths
target_include_directories(regular_languages_components PUBLIC
    $<BUILD_INTERFACE:${formal_languages_source_dir}>
    $<INSTALL_INTERFACE:include>
)

# Add library target
#add_library(regular_languages_components_static STATIC ${regular_languages_components_source})

# Tell cmake target's dependencies
#target_link_libraries(regular_languages_components_static
#)

# Tell cmake the path to look for include files for this target
# This is transitive, so any targets linked with this one will
# search for headers in the respective paths
#target_include_directories(regular_languages_components_static PUBLIC
#    $<BUILD_INTERFACE:${regular_languages_source_dir}>
#    $<INSTALL_INTERFACE:include>
#)
