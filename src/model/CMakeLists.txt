################################################################################
# This is the CMakeLists file for the:
#
#   namespace formal_languages::parser
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
set(formal_languages_model_install_include_dir 
    ${formal_languages_install_include_dir}/formal_languages/parser
)

################################################################################
# Fetch files
################################################################################

# Fetch .ccp files for library creation
file(GLOB formal_languages_model_source
    "*.cpp"
)

# Fetch .h files for library creation
file(GLOB formal_languages_model_headers
    "*.h"
)

################################################################################
# Library target
################################################################################

# Add library target
add_library(formal_languages_model SHARED ${formal_languages_model_source})

# Set shared library version, this will make cmake create a link
set_target_properties(formal_languages_model PROPERTIES
    VERSION ${formal_languages_VERSION}
    SOVERSION ${formal_languages_VERSION}
)

# Tell cmake target's dependencies
#target_link_libraries(formal_languages_model
#    PRIVATE 
#)

# Tell cmake the path to look for include files for this target
# This is transitive, so any targets linked with this one will
# search for headers in the respective paths
target_include_directories(formal_languages_model PUBLIC
    $<BUILD_INTERFACE:${formal_languages_source_dir}>
    $<INSTALL_INTERFACE:include>
)

# Add library target
add_library(formal_languages_model_static STATIC ${formal_languages_model_source})

# Tell cmake target's dependencies
#target_link_libraries(formal_languages_model_static
#)

# Tell cmake the path to look for include files for this target
# This is transitive, so any targets linked with this one will
# search for headers in the respective paths
target_include_directories(formal_languages_model_static PUBLIC
    $<BUILD_INTERFACE:${formal_languages_source_dir}>
    $<INSTALL_INTERFACE:include>
)
