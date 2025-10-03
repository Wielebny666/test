cmake_minimum_required(VERSION 3.28)
project(FWLibraryUnitTests)
include(CTest)

set(CMAKE_C_STANDARD 17 CACHE INTERNAL "C standard for all targets")
set(CMAKE_CXX_STANDARD 17 CACHE INTERNAL "C++ standard for all targets")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF CACHE INTERNAL "C compiler extensions OFF")
set(CMAKE_CXX_EXTENSIONS OFF CACHE INTERNAL "C++ compiler extensions OFF")

###################################################
# Add tests to this list (TEST_SUITES)
###################################################
LIST(APPEND TEST_SUITES
        IpManager
    #  Actuator
    #  AsyncProcessor
    #  Components
    #  Console
    #  CPUStatModule
    #  Debug
    #  DeviceInfo
    #  DeviceTreeParser
    #  FileSystem
    #  hw
    #  List
    #  Logs
    #  OneWire
    #  PressureInput
    #  Statistics
    #  Thread
    #  Utils
     )

###################################################

add_compile_options(-Wall -Wextra -Werror)

if(DEFINED UT_DBG_LOGS)
    add_compile_definitions(UT_DBG_LOGS=${UT_DBG_LOGS})
endif()

if(DEFINED DBG_DEVELOPMENT_LOGS)
    add_compile_definitions(DBG_DEVELOPMENT_LOGS=${DBG_DEVELOPMENT_LOGS})
endif()

# enable sanitizers
add_compile_options(-fsanitize=address -fsanitize=undefined)
add_link_options(-fsanitize=address -fsanitize=undefined)

#add search path for sublibraries
set(ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/../..")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}")

include(FetchContent)

include(../GoogleTestsPrepare)

###################################################
# Helper functions
###################################################

function(AddMock library)
  include(${library}/mock)
endfunction()

function(AddStub library)
  include(${library}/stub)
endfunction()

function(AddSource library)
  set(PROJECT_NAME_STATIC ${PROJECT_NAME})
  include(${library}/source)
endfunction()

function(AddInterface library)
  include(${library}/interface)
endfunction()

function(AddLibrary library)
  message("${ROOT_DIR}/${library} ${library}")
  add_subdirectory("${ROOT_DIR}/${library}" "${library}")
endfunction()

###################################################

foreach(subdir ${TEST_SUITES})
  add_subdirectory(${subdir})
endforeach()
