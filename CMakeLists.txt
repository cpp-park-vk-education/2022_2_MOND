cmake_minimum_required(VERSION 3.0)
project(MOND_DB CXX)

set(CMAKE_CXX_STANDARD 17)

option(SERVERDB_BUILD "Server build" OFF)
option(CLIENTDB_BUILD "Client build" ON)
option(DEBUG_BUILD "Build for test" ON)

add_subdirectory(project)

add_executable(${PROJECT_NAME} main.cpp)
if (DEBUG_BUILD)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )
endif ()


set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${PROJECT_SOURCE_DIR}/CMake")

#include(coverage)

enable_testing()
#add_coverage_target("Tests/*")//не получилось(((
add_subdirectory(Tests)
