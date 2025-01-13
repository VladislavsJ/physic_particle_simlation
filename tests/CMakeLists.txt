cmake_minimum_required(VERSION 3.10)

# Set the project name
project(PhysicsBalls)

# Enable testing
enable_testing()

# Find GTest
find_package(GTest REQUIRED)

# Include directories
include_directories(
    ../src
)

# Test source files
file(GLOB TEST_SOURCES "*.cpp")

# Test executable
add_executable(tests
    ${TEST_SOURCES}
    ../src/Particle.cpp
    ../src/ParticleSystem.cpp
    ../src/Vector2D.hpp  # Removed if header-only
    ../src/Physics.cpp
    ../src/BorderInfo.cpp
)

# Link libraries
target_link_libraries(tests
    PRIVATE
        GTest::GTest
        GTest::Main
        pthread
)

# Register the tests
add_test(NAME tests COMMAND tests)
