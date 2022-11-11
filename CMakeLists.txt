cmake_minimum_required(VERSION 3.0)
project(MOND_DB CXX)

set(CMAKE_CXX_STANDARD 17)

# options for build
option(DEBUG_BUILD "Debug build" ON)
option(RELEASE_BUILD "Release build" OFF)

option(SERVERDB_BUILD "Server build" ON)
option(CLIENTDB_BUILD "Client build" ON)

include(CMake/clangformat.cmake)
# cmake --build build --target clangformat
# or
# cd build
# make clangformat
clangformat_setup(
        Tests/tests.cpp
        main.cpp
)

# adding flags for current project
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -Wconversion")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wunreachable-code -pedantic -pthread")

if (RELEASE_BUILD)
    # adding additional flags for release build
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

    add_subdirectory(project)

elseif(DEBUG_BUILD)
    # adding additional flags for debug build
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -fprofile-arcs -ftest-coverage -fPIC")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )
    #include(coverage)
    add_subdirectory(Tests)
    enable_testing()
    #add_coverage_target("Tests/*")//не получилось(((
    add_subdirectory(project)
endif()

set(CMAKE_CXX_CLANG_TIDY
        clang-tidy;
        -header-filter=.;
        -checks=*;
        -warnings-as-errors=*;
        -extra-arg=-std=c++17;)
