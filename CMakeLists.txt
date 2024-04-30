cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 20)

set(EXECUTABLE_NAME "powdersim")
set(PROJECT_NAME "Powder Simulator")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # generates clangd file

project(${PROJECT_NAME} VERSION 0.1)

# recursively finds .cpp files in src/ and adds them to the target
file(GLOB_RECURSE SOURCES "src/*.cpp")

# ;main.cpp adds driver file to target
add_executable(${EXECUTABLE_NAME} "${SOURCES}")

# enable maximum warnings
target_compile_options(${EXECUTABLE_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)

# looks in src/ for include directories
target_include_directories(${EXECUTABLE_NAME} PRIVATE "src")

# links SFML
find_package(SFML REQUIRED COMPONENTS graphics system window)
target_link_libraries(${EXECUTABLE_NAME} sfml-graphics sfml-system sfml-window)
