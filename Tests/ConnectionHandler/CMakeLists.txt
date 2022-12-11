cmake_minimum_required(VERSION 3.0)
project(CONNECTION_HANDLER_TESTS CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)

clangformat_setup(
        tests.cpp
)

add_executable(${PROJECT_NAME} tests.cpp)
target_link_libraries(${PROJECT_NAME} GTest::gtest_main GTest::gmock_main)
target_include_directories(${PROJECT_NAME} PUBLIC ${CONNECTION_HANDLER_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${CONNECTION_HANDLER_LIBRARIES})

enable_testing()