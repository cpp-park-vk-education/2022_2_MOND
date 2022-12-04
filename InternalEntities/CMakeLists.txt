cmake_minimum_required(VERSION 3.0)
project(InternalEntities CXX)

if (DEBUG_BUILD)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -ftest-coverage -O0")
endif ()

find_package(Boost REQUIRED COMPONENTS serialization)

file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

add_library(${PROJECT_NAME} INTERFACE)

set(ENTITIES_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(ENTITIES_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)

target_include_directories(${PROJECT_NAME} INTERFACE ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} INTERFACE Boost::serialization)
