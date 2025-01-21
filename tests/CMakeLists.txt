cmake_minimum_required(VERSION 3.10)

# Set the project name
project(PhysicsBalls)

# Enable testing
enable_testing()

# Find required packages
find_package(GTest REQUIRED)
find_package(OpenMP REQUIRED)
find_package(SFML COMPONENTS graphics window system REQUIRED)

# Define source directories
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../src)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Collect all source files
file(GLOB_RECURSE SRC_FILES 
    "${SRC_DIR}/*.cpp"
)

# Collect all test files
file(GLOB_RECURSE TEST_FILES 
    "${TEST_DIR}/*.cpp"
)

# Create list of header files (optional, for IDE support)
file(GLOB_RECURSE HEADER_FILES 
    "${SRC_DIR}/*.hpp"
    "${SRC_DIR}/*.h"
)

# Create library from source files
add_library(physics_lib STATIC ${SRC_FILES} ${HEADER_FILES})
target_include_directories(physics_lib PUBLIC ${SRC_DIR})
target_link_libraries(physics_lib
    PUBLIC
        sfml-graphics
        sfml-window
        sfml-system
        OpenMP::OpenMP_CXX
)

# Test executable
add_executable(tests ${TEST_FILES})
target_include_directories(tests PRIVATE ${SRC_DIR})
target_link_libraries(tests
    PRIVATE
        physics_lib
        GTest::GTest
        GTest::Main
        pthread
)

# Register the tests
add_test(NAME tests COMMAND tests)

# Set C++ standard for all targets
set_target_properties(physics_lib tests
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)