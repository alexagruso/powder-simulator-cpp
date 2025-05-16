cmake_minimum_required(VERSION 3.28)
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
add_executable(${PROJECT_EXECUTABLE} "${PROJECT_SOURCES}")

# enable maximum warnings
target_compile_options(${PROJECT_EXECUTABLE} PRIVATE -Wall -Wextra -Wpedantic -Werror)

# searches src/ for header files included in the project
target_include_directories(${PROJECT_EXECUTABLE} PRIVATE "src")

# links SFML to the project executable
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)
target_link_libraries(${PROJECT_EXECUTABLE} PRIVATE sfml-graphics)
