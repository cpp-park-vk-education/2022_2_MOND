cmake_minimum_required(VERSION 3.0)
project(MOND_DB CXX)

set(CMAKE_CXX_STANDARD 17)

option(DEBUG_BUILD "Debug build" ON)
option(RELEASE_BUILD "Release build" OFF)

option(ADDRESS_SANITIZER_BUILD "detecting  memory errors" ON)
option(LEAK_SANITIZER_BUILD "detecting memory leaks" ON)
option(UNDEFINED_BEHAVIOUR_SANITIZER_BUILD "detecting undefined behaviour" ON)
option(THREAD_SANITIZER_BUILD "detecting data races for multi-threaded code" OFF)

option(SERVERDB_BUILD "Server build" ON)
option(CLIENTDB_BUILD "Client build" ON)

include(CMake/clangformat.cmake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -Wconversion")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunreachable-code -pedantic -pthread")

if (RELEASE_BUILD)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

elseif (DEBUG_BUILD)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -fprofile-arcs -ftest-coverage -fPIC")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov")

    if (ADDRESS_SANITIZER_BUILD)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
    endif ()

    if (UNDEFINED_BEHAVIOUR_SANITIZER_BUILD)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
    endif ()

    if (THREAD_SANITIZER_BUILD)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread")
    endif ()

    if (LEAK_SANITIZER_BUILD)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak")
    endif ()
endif ()

add_subdirectory(InternalEntities)

add_subdirectory(DBCore)

add_subdirectory(ConnectionHandler)

add_subdirectory(Initializer)

if (CLIENTDB_BUILD)
    add_subdirectory(ClientDB)
endif ()

if (SERVERDB_BUILD)
    add_subdirectory(ServerDB)
endif ()

add_subdirectory(Tests/HashTable)

add_subdirectory(Tests/Request_Serializer)

add_subdirectory(Tests/TableStorage)

add_subdirectory(Tests/ConnectionHandler)

add_subdirectory(Tests/Initializer)

add_subdirectory(Tests/ClientDB)


