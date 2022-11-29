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

#set(CMAKE_CXX_CLANG_TIDY
#        clang-tidy;
#        -header-filter=.;
#        -checks=*;
#        -warnings-as-errors=*;
#        -extra-arg=-std=c++17;)

add_subdirectory(InternalEntities)

add_subdirectory(DBCore)

add_subdirectory(Serializer)

add_subdirectory(Tests/TablesLogic)

add_subdirectory(Tests/Serializer)
