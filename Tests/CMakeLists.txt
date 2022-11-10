cmake_minimum_required(VERSION 3.0)
project(MOND_DB_TESTS CXX)

set(CMAKE_CXX_STANDARD 17)


set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-O0 -Wall -Wextra -Werror -Wpedantic -fprofile-arcs -ftest-coverage -fPIC")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov")


find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} tests.cpp)
target_link_libraries(${PROJECT_NAME} GTest::gtest_main)
