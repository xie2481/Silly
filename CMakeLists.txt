cmake_minimum_required(VERSION 2.8)
project(Silly)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O3 -g -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function")
set(LIB_SRC
    Silly/log.cc
    Silly/util.cc
    )

add_library(Silly SHARED ${LIB_SRC})

add_executable(tests tests/test.cc)
add_dependencies(tests Silly)
target_link_libraries(tests Silly)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
