cmake_minimum_required(VERSION 2.8)
project(Silly)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O3 -g -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function")

include_directories(.)
include_directories(~/Silly/include)

link_directories("~/Silly/lib")

set(LIB_SRC
    Silly/log.cc
    Silly/util.cc
    Silly/config.cc
    Silly/thread.cc
    Silly/fiber.cc
    )

set(LIB
    yaml-cpp
    pthread
    )
add_library(Silly SHARED ${LIB_SRC})

add_executable(testconfig tests/test_config.cc)
add_dependencies(testconfig Silly)
target_link_libraries(testconfig Silly "${LIB}")

add_executable(testthread_log tests/test_threadlog.cc)
add_dependencies(testthread_log Silly)
target_link_libraries(testthread_log Silly "${LIB}")

add_executable(testassert tests/test_assert.cc)
add_dependencies(testassert Silly)
target_link_libraries(testassert Silly "${LIB}")

add_executable(testfiber tests/test_fiber.cc)
add_dependencies(testfiber Silly)
target_link_libraries(testfiber Silly "${LIB}")

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
