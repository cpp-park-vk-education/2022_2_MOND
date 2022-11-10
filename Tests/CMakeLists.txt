cmake_minimum_required(VERSION 3.0)
project(DB_Interface_tests CXX)

set(CMAKE_CXX_STANDARD 17)

if (BUILD_FOR_TEST)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-ftest-coverage -O0")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )
endif ()

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} tests.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${HASHTABLE_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${HASHTABLE_LIBRARIES} GTest::gtest_main)

enable_testing()
add_test(NAME DB_Interface_Tests COMMAND DB_Interface_Tests)
