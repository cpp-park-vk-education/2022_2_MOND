cmake_minimum_required(VERSION 3.23)
project(ACCESS_CONTROLLER_TESTS CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)

clangformat_setup(
        tests.cpp
)

add_executable(${PROJECT_NAME} tests.cpp)
target_link_libraries(${PROJECT_NAME} GTest::gtest_main)
target_include_directories(${PROJECT_NAME} PUBLIC ${ACCESS_CONTROLLER_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${ACCESS_CONTROLLER_LIBRARIES})

enable_testing()