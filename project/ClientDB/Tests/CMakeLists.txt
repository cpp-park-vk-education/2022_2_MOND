cmake_minimum_required(VERSION 3.0)
project(MOND_DB_CLIENT_TESTS CXX)

set(CMAKE_CXX_STANDARD 17)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -Wextra -Werror -Wpedantic -fprofile-arcs -ftest-coverage -fPIC")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov -pthread")

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} tests.cpp ${CLIENT_DB_EXECUTABLES})

target_link_libraries(${PROJECT_NAME} GTest::gtest_main)

target_link_libraries(
        ${PROJECT_NAME}
        ${LIB_CONNECTOR_LIBRARIES}
)

target_include_directories(
        ${PROJECT_NAME} PUBLIC
        ${LIB_CONNECTOR_INCLUDE_DIRS}
        ${CLIENT_DB_INCLUDE_DIRS}
)
enable_testing()
add_test(NAME test_mul COMMAND A_mul_B)