cmake_minimum_required(VERSION 3.0)
project(MOND_DB CXX)

option(DEBUG_BUILD "Build for test" OFF)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp)
if (DEBUG_BUILD)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )
endif ()

enable_testing()

add_subdirectory(Tests)
