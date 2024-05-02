cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 20)

set(PROJECT_NAME "Powder Simulator")
project(${PROJECT_NAME} VERSION 0.1)

# generates clangd file for lsp
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

###################
# Main Executable #
###################

set(PROJECT_EXECUTABLE "powdersim")

# recursively finds .cpp files in src/ and adds them to the main executable
file(GLOB_RECURSE PROJECT_SOURCES "src/*.cpp")

# generates project executable
add_executable(${PROJECT_EXECUTABLE} "${PROJECT_SOURCES}")

# enable maximum warnings
target_compile_options(${PROJECT_EXECUTABLE} PRIVATE -Wall -Wextra -Wpedantic -Werror)

# searches src/ for header files included in the project
target_include_directories(${PROJECT_EXECUTABLE} PRIVATE "src")

# links SFML to the project executable
find_package(SFML REQUIRED COMPONENTS graphics system window)
target_link_libraries(${PROJECT_EXECUTABLE} sfml-graphics sfml-system sfml-window)

###################
# Test Executable #
###################

set(TEST_EXECUTABLE "unit_tests")

# removes project driver src/main.cpp from test executable
list(FILTER PROJECT_SOURCES EXCLUDE REGEX "src/main.cpp")
# recursively finds source files in tests/ and adds them to the testing executable
file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")

# generates test executable
add_executable(${TEST_EXECUTABLE} "${TEST_SOURCES};${PROJECT_SOURCES}")

# searches src/ and test/ for header files included in the tests
target_include_directories(${TEST_EXECUTABLE} PRIVATE "src")
target_include_directories(${TEST_EXECUTABLE} PRIVATE "tests")

# links Catch2 and SFML to the test executable
find_package(Catch2 3 REQUIRED)
target_link_libraries(${TEST_EXECUTABLE} PRIVATE Catch2::Catch2WithMain sfml-graphics sfml-system sfml-window)
