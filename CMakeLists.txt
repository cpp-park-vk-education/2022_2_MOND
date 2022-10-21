cmake_minimum_required(VERSION 3.0)
project(MOND_DB CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS --coverage)

add_subdirectory(Tests)

enable_testing()
add_test(NAME MOND_DB_TESTS COMMAND MOND_DB_TESTS)