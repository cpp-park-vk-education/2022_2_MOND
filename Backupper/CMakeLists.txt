cmake_minimum_required(VERSION 3.23)
project(Backupper)
set(CMAKE_CXX_STANDARD 17)

if (DEBUG_BUILD)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -ftest-coverage -O0")
endif ()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread")

file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})
find_package(Boost COMPONENTS serialization filesystem REQUIRED)
add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} PUBLIC INTERFACE ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} INTERFACE Boost::filesystem Boost::serialization)

target_include_directories(${PROJECT_NAME} PUBLIC INTERFACE ${ENTITIES_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} INTERFACE ${ENTITIES_LIBRARIES})

set(BACKUPPER_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(BACKUPPER_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)
