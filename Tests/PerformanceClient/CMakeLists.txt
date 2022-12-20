cmake_minimum_required(VERSION 3.23)
project(PERFORMANCE_CLIENT CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)

clangformat_setup(
        client.cpp
)

add_executable(${PROJECT_NAME} client.cpp)
#target_link_libraries(${PROJECT_NAME} GTest::gtest_main GTest::gmock_main)
target_include_directories(${PROJECT_NAME} PUBLIC ${CLIENT_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${CLIENT_LIBRARIES})

enable_testing()