cmake_minimum_required(VERSION 3.23)
project(CLIENT_TESTS CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS thread)

clangformat_setup(
        tests.cpp
)

add_executable(${PROJECT_NAME} tests.cpp)
target_link_libraries(${PROJECT_NAME} GTest::gtest_main GTest::gmock_main)

target_include_directories(${PROJECT_NAME} PUBLIC ${CLIENT_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${CLIENT_LIBRARIES})

target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} Boost::thread)

enable_testing()
add_test(NAME SERIALIZER_tests COMMAND SERIALIZER_tests)






