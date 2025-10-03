cmake_minimum_required(VERSION 3.28)

project(IpManagerTest)


add_executable(${PROJECT_NAME})

# treat private members as public
target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fno-access-control>)

target_sources(
    ${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/IpManagerTest.cpp
)

target_include_directories(
    ${PROJECT_NAME} PUBLIC
)

# Add dependecies
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    GTest::gtest_main
    GTest::gmock
    test::IpManager
)

include(GoogleTest)

gtest_discover_tests(${PROJECT_NAME})

