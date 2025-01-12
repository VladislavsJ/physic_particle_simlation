cmake_minimum_required(VERSION 3.10)
project(ParticleSimulator)

set(CMAKE_CXX_STANDARD 17)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add subdirectory for tests
add_subdirectory(tests)

# Source files
file(GLOB PARTICLE_SIM_SRC
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/*.h"
)

# Create the main executable
add_executable(ParticleSimulator ${PARTICLE_SIM_SRC})
target_link_libraries(ParticleSimulator sfml-graphics sfml-window sfml-system)
find_package(GTest)
if(GTEST_FOUND)
    add_subdirectory(tests)
else()
    message(WARNING "GTest not found - skipping tests")
endif()

