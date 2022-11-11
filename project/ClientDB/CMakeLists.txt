cmake_minimum_required(VERSION 3.0)
project(MOND_DB_CLIENT CXX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(LibConnector)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -Wall -Wextra -pedantic -Wformat=2 -Wfloat-equal -Wconversion -fprofile-arcs")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -Wlogical-op  -Wduplicated-cond -Wcast-qual -Wcast-align")

set(HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/headers/header.hpp
        )

set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/source.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/main.cpp
        )

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(
        ${PROJECT_NAME}
        ${LIB_CONNECTOR_LIBRARIES}
)

target_include_directories(
        ${PROJECT_NAME} PUBLIC
        ${LIB_CONNECTOR_INCLUDE_DIRS}
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/headers)

if (DEBUG_BUILD)
    message("DEBUG BUILD CLIENT")
    set(CLIENT_DB_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/headers)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )
    add_subdirectory(Tests)
    enable_testing()
endif ()
