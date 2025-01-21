cmake_minimum_required(VERSION 3.10)
project(ParticleSimulator)

set(CMAKE_CXX_STANDARD 17)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

find_package(OpenMP REQUIRED)         # Finds the OpenMP package
# Source files
file(GLOB PARTICLE_SIM_SRC
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/*.h"
)

# Main application
add_executable(ParticleSimulator ${PARTICLE_SIM_SRC})
target_link_libraries(ParticleSimulator sfml-graphics sfml-window sfml-system OpenMP::OpenMP_CXX)

# Optionally control whether tests get built
option(BUILD_TESTING "Build tests" ON)

if (BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
