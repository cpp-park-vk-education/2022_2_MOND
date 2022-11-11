cmake_minimum_required(VERSION 3.0)
project(MOND_DB CXX)

set(CMAKE_CXX_STANDARD 17)

# options for build
option(DEBUG_BUILD "Debug build" ON)
option(RELEASE_BUILD "Release build" OFF)

option(SERVERDB_BUILD "Server build" OFF)
option(CLIENTDB_BUILD "Client build" ON)

# adding flags for current project
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -Wconversion -Werror -Wunreachable-code -pedantic")

if (RELEASE_BUILD)
    # adding additional flags for release build
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

    add_subdirectory(project)

elseif(DEBUG_BUILD)
    # adding additional flags for debug build
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

    add_subdirectory(Tests)
    enable_testing()

    add_subdirectory(project)
endif()


#add_executable(${PROJECT_NAME} main.cpp)
#if (DEBUG_BUILD)
#    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )
#endif ()
#
#
#set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${PROJECT_SOURCE_DIR}/CMake")
#
##include(coverage)
#
#enable_testing()
##add_coverage_target("Tests/*")//не получилось(((
#add_subdirectory(Tests)
