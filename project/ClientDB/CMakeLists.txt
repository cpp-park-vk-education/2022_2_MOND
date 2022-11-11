cmake_minimum_required(VERSION 3.0)
project(MOND_DB_CLIENT CXX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(LibConnector)

# adding source files of current project
set(HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/headers/header.hpp
        )
set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/source.cpp
        )
add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/sources/main.cpp ${SOURCES} ${HEADERS})

clangformat_setup(
        ${SOURCES}
        ${HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/main.cpp
)

# adding libraries for this project, e.g. LibConnector
target_link_libraries(
        ${PROJECT_NAME}
        ${LIB_CONNECTOR_LIBRARIES}
)
target_include_directories(
        ${PROJECT_NAME} PUBLIC
        ${LIB_CONNECTOR_INCLUDE_DIRS}
)

# make functions in ./headers/*.hpp available from source files
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/headers)

if (DEBUG_BUILD)
    # make functions in source files of this project (except main.cpp) available for tests (e.g. sum())
    set(CLIENT_DB_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/headers ${CMAKE_CURRENT_SOURCE_DIR}/sources)

    # make source files of this project (except main.cpp) available for tests
    set(CLIENT_DB_EXECUTABLES ${SOURCES} ${HEADERS})

    # additional flags when DEBUG_BUILD
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )
    add_subdirectory(Tests)
    enable_testing()
    add_test(NAME test_mul COMMAND A_mul_B)
endif ()
