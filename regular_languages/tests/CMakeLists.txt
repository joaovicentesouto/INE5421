################################################################################
# This is the CMakeLists file for the regular_languages' tests directory.
#
################################################################################

# Fetch test files recursevely
file(GLOB_RECURSE regular_languages_tests_source
    "*.cpp"
    "main.cpp"
)

# Add test target
add_executable(regular_languages_tests ${regular_languages_tests_source})

target_link_libraries(regular_languages_tests
    PRIVATE regular_languages_components
    PRIVATE regular_languages_devices
    PRIVATE regular_languages_parsers
    PRIVATE regular_languages_manipulators
)

################################################################################
# Add test to ctest
################################################################################

enable_testing()
add_test(NAME unit_test COMMAND regular_languages_tests)
