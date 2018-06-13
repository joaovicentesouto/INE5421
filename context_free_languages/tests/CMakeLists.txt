################################################################################
# This is the CMakeLists file for the regular_languages' tests directory.
#
################################################################################

# Fetch test files recursevely
file(GLOB_RECURSE context_free_languages_tests_source
    "*.cpp"
    "main.cpp"
)

# Add test target
add_executable(context_free_languages_tests ${context_free_languages_tests_source})

target_link_libraries(context_free_languages_tests
    PRIVATE context_free_languages_components
    PRIVATE context_free_languages_devices
    PRIVATE context_free_languages_parsers
    # PRIVATE context_free_languages_manipulators
)

################################################################################
# Add test to ctest
################################################################################

enable_testing()
add_test(NAME unit_test COMMAND context_free_languages_tests)
