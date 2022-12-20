cmake_minimum_required(VERSION 3.0)
project(CONNECTION_HANDLER CXX)

set(CMAKE_CXX_STANDARD 17)

set(INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

set(HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/ConnectionHandler.hpp
        )

set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/ConnectionHandler.cpp
        )

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME}
        ${BOOST_IFACE_LIBRARIES}
        ${ENTITIES_LIBRARIES}
        ${CONNECTION_WORKER_LIBRARIES}
        )
target_include_directories(${PROJECT_NAME} PUBLIC
        ${BOOST_IFACE_INCLUDE_DIRS}
        ${ENTITIES_INCLUDE_DIRS}
        ${CONNECTION_WORKER_INCLUDE_DIRS}
        )

set(${PROJECT_NAME}_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(${PROJECT_NAME}_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)

set(CMAKE_CXX_CLANG_TIDY
        clang-tidy;
        -header-filter=.;
        -checks=*;
        -warnings-as-errors=*;
        -extra-arg=-std=c++17;)
