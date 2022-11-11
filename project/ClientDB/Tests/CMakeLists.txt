cmake_minimum_required(VERSION 3.0)
project(MOND_DB_CLIENT_TESTS CXX)

set(CMAKE_CXX_STANDARD 17)


set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-O0 -Wall -Wextra -Werror -Wpedantic -fprofile-arcs -ftest-coverage -fPIC")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov")

#############
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
#############

FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME} tests.cpp)
target_link_libraries(${PROJECT_NAME} gtest_main)

target_link_libraries(
        ${PROJECT_NAME}
        ${LIB_CONNECTOR_LIBRARIES}
)

target_include_directories(
        ${PROJECT_NAME} PUBLIC
        ${LIB_CONNECTOR_INCLUDE_DIRS}
        ${CLIENT_DB_INCLUDE_DIRS}
)