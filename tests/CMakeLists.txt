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
    PRIVATE formal_languages_devices
    PRIVATE formal_languages_parsers
)

message("Creating symlink for test files")
execute_process(
    COMMAND ln -f -s ${PROJECT_SOURCE_DIR}/tests/files ${PROJECT_BINARY_DIR}/tests/.
    RESULT_VARIABLE result
)


################################################################################
# Add test to ctest
################################################################################

enable_testing()
add_test(NAME unit_test COMMAND formal_languages_tests)
