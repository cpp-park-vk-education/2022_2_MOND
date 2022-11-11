cmake_minimum_required(VERSION 3.0)
project(LIB_CONNECTOR CXX)

set(CMAKE_CXX_STANDARD 17)

set(INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

set(HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/Connector.hpp
        )

set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/Connector.cpp
        )

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

set(LIB_CONNECTOR_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(LIB_CONNECTOR_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)

set(CMAKE_CXX_CLANG_TIDY
        clang-tidy;
        -header-filter=.;
        -checks=*;
        -warnings-as-errors=*;
        -extra-arg=-std=c++17;)
