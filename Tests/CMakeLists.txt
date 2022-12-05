cmake_minimum_required(VERSION 3.0)
project(MOND_DB_TESTS CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)

clangformat_setup(
        tests.cpp
)

add_executable(${PROJECT_NAME} tests.cpp)
target_link_libraries(${PROJECT_NAME} GTest::gtest_main)
target_include_directories(${PROJECT_NAME} PUBLIC ${DBCORE_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${DBCORE_LIBRARIES})

add_subdirectory(HashTable)

add_subdirectory(TableStorage)
