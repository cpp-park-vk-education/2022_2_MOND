cmake_minimum_required(VERSION 3.0)
project(MOND_DB_PROJECT CXX)

if(SERVERDB_BUILD)
    message("BUILDING SERVER...")
    add_subdirectory(ServerDB)
endif()

if(CLIENTDB_BUILD)
    message("BUILDING CLIENT...")
    add_subdirectory(ClientDB)
endif()

set(CMAKE_CXX_CLANG_TIDY
        clang-tidy;
        -header-filter=.;
        -checks=*;
        -warnings-as-errors=*;
        -extra-arg=-std=c++17;)
