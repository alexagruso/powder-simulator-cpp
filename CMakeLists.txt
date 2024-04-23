cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 20)

set(PROJECT_NAME "Powder Simulator")
project(${PROJECT_NAME} VERSION 0.1)

# CMake config
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # generates clangd file

##################
# Main Executable
##################

set(PROJECT_EXECUTABLE "powdersim")

# recursively finds .cpp files in src/ and adds them to the main executable
file(GLOB_RECURSE PROJECT_SOURCES "src/*.cpp")

# ;main.cpp adds driver file to target
add_executable(${PROJECT_EXECUTABLE} "${PROJECT_SOURCES};main.cpp")

# looks in src/ for include directories
target_include_directories(${PROJECT_EXECUTABLE} PRIVATE "src")

# links SFML
find_package(SFML REQUIRED COMPONENTS graphics system window)
target_link_libraries(${PROJECT_EXECUTABLE} sfml-graphics sfml-system sfml-window)

##################
# Test Executable
##################

set(TEST_EXECUTABLE "powdersim_tests")

# recursively finds .cpp files in tests/ and adds them to the testing executable
file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")

# ;main.cpp adds driver file to target
add_executable(${TEST_EXECUTABLE} ${TEST_SOURCES})

# looks in tests/ for include directories
target_include_directories(${TEST_EXECUTABLE} PRIVATE "tests")

# links Catch2
find_package(Catch2 3 REQUIRED)
target_link_libraries(${TEST_EXECUTABLE} PRIVATE Catch2::Catch2WithMain)
