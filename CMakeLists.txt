cmake_minimum_required(VERSION 2.8)
project(Silly)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O3 -g -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function")

include_directories(.)
include_directories(/home/xie2481/Silly/include)

link_directories("/home/xie2481/Silly/lib")

set(LIB_SRC
    Silly/log.cc
    Silly/util.cc
    Silly/config.cc
    )

set(LIB
    yaml-cpp
    )
add_library(Silly SHARED ${LIB_SRC})

add_executable(testconfig tests/test_config.cc)
add_dependencies(testconfig Silly)
target_link_libraries(testconfig Silly "${LIB}")

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
