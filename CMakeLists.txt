cmake_minimum_required(VERSION 3.28)

project(FWLibrary)

message(STATUS "FW_Library included")

if(NOT DEFINED BUILD_TESTS)
    set(BUILD_TESTS FALSE CACHE BOOL "Build project tests")
endif()

# this is needed to create compile_commands.json file needed for SonarLint extension
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_STANDARD 17 CACHE INTERNAL "C standard for all targets")
set(CMAKE_CXX_STANDARD 17 CACHE INTERNAL "C++ standard for all targets")
set(CMAKE_C_EXTENSIONS OFF CACHE INTERNAL "C compiler extensions OFF")
set(CMAKE_CXX_EXTENSIONS OFF CACHE INTERNAL "C++ compiler extensions OFF")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(${PROJECT_NAME} INTERFACE)

add_subdirectory(IpManager)

enable_testing()

if(BUILD_TESTS)
    add_subdirectory(test/UnitTest)
endif()

