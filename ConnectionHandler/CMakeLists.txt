cmake_minimum_required(VERSION 3.23)
project(ConnectionHandler)

if (DEBUG_BUILD)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -ftest-coverage -O0")
endif ()

find_package(Boost COMPONENTS thread REQUIRED)

file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})


add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} PUBLIC INTERFACE ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} INTERFACE Boost::thread)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread -lboost_thread")

target_include_directories(${PROJECT_NAME} PUBLIC INTERFACE ${DBCORE_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} INTERFACE ${DBCORE_LIBRARIES})

target_include_directories(${PROJECT_NAME} PUBLIC INTERFACE ${ENTITIES_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} INTERFACE ${ENTITIES_LIBRARIES})

target_include_directories(${PROJECT_NAME} PUBLIC INTERFACE ${ACCESS_CONTROLLER_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} INTERFACE ${ACCESS_CONTROLLER_LIBRARIES})

set(CONNECTION_HANDLER_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(CONNECTION_HANDLER_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)
