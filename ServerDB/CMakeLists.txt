cmake_minimum_required(VERSION 3.0)
project(SERVER_DB CXX)

set(CMAKE_CXX_STANDARD 17)

clangformat_setup(
        main.cpp
)

add_executable(${PROJECT_NAME} main.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${INITIALIZER_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${INITIALIZER_LIBRARIES})
