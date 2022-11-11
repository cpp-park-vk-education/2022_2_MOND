cmake_minimum_required(VERSION 3.0)
project(MOND_DB_SERVER_TESTS CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} tests.cpp ${SERVER_DB_EXECUTABLES})

target_link_libraries(${PROJECT_NAME} GTest::gtest_main)

target_link_libraries(
        ${PROJECT_NAME}
        ${LIB_CONNECTOR_LIBRARIES}
)

clangformat_setup(
        tests.cpp
)

target_include_directories(
        ${PROJECT_NAME} PUBLIC
        ${LIB_CONNECTOR_INCLUDE_DIRS}
        ${SERVER_DB_INCLUDE_DIRS}
)
enable_testing()
add_test(NAME test_mul COMMAND A_mul_B)