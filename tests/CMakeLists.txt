cmake_minimum_required(VERSION 3.10)

find_package(GTest REQUIRED)

# Collect all test source files
file(GLOB TEST_SOURCES "*.cpp")

# Test executable
add_executable(tests ${TEST_SOURCES})

# Link libraries
target_link_libraries(tests
    PRIVATE
        GTest::GTest
        GTest::Main
        pthread
)

# Register the tests
add_test(NAME tests COMMAND tests)
