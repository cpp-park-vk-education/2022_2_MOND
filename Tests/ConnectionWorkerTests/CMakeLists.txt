cmake_minimum_required(VERSION 3.0)
project(CONNECTION_WORKER_TESTS CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wconversion -Wpedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunreachable-code -pedantic -pthread")

if (DEBUG_BUILD)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -fprofile-arcs -ftest-coverage -fPIC")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )
endif ()

find_package(GTest REQUIRED)

clangformat_setup(
        tests.cpp
)

add_executable(${PROJECT_NAME} tests.cpp)
target_link_libraries(${PROJECT_NAME} GTest::gtest_main)
target_include_directories(${PROJECT_NAME} PUBLIC ${CONNECTION_WORKER_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${CONNECTION_WORKER_LIBRARIES})

set(CMAKE_CXX_CLANG_TIDY
        clang-tidy;
        -header-filter=.;
        -checks=*;
        -warnings-as-errors=*;
        -extra-arg=-std=c++17;)

enable_testing()