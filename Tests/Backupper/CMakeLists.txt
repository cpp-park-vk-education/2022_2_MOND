cmake_minimum_required(VERSION 3.23)
project(BACKUPPER_TESTS CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest CONFIG REQUIRED)

clangformat_setup(
        tests.cpp
)

add_executable(${PROJECT_NAME} tests.cpp)
target_link_libraries(${PROJECT_NAME} GTest::gtest_main GTest::gmock_main)

target_include_directories(${PROJECT_NAME} PUBLIC ${BACKUPPER_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${BACKUPPER_LIBRARIES})

enable_testing()
add_test(NAME BACKUPPER_tests COMMAND BACKUPPER_tests)
