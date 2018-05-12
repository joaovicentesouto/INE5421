################################################################################
# This is the CMakeLists file for the formal_languages' tests directory.
#
################################################################################

# Fetch test files recursevely
file(GLOB_RECURSE formal_languages_tests_source
    "*.cpp"
    "main.cpp"
)

# Add test target
add_executable(formal_languages_tests ${formal_languages_tests_source})

target_link_libraries(formal_languages_tests
    PRIVATE formal_languages_model
)


################################################################################
# Add test to ctest
################################################################################

enable_testing()
add_test(NAME unit_test COMMAND formal_languages_tests)
