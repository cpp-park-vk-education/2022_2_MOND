cmake_minimum_required(VERSION 3.0)
project(SERIALIZER_TESTS CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wconversion -Wpedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunreachable-code -pedantic -pthread")

if (DEBUG_BUILD)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -fprofile-arcs -ftest-coverage -fPIC")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )
endif ()

find_package(GTest CONFIG REQUIRED)

clangformat_setup(
        tests.cpp
)

add_executable(${PROJECT_NAME} tests.cpp)
target_link_libraries(${PROJECT_NAME} GTest::gtest_main GTest::gmock_main)
target_include_directories(${PROJECT_NAME} PUBLIC ${SERIALIZER_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SERIALIZER_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC ${ENTITIES_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${ENTITIES_LIBRARIES})

enable_testing()
add_test(NAME SERIALIZER_tests COMMAND SERIALIZER_tests)
