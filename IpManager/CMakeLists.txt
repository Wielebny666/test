cmake_minimum_required(VERSION 3.28)

project(IpManager)

add_library(${PROJECT_NAME} STATIC)
add_library(test::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

include(source.cmake)
