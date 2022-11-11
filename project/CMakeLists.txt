cmake_minimum_required(VERSION 3.0)
project(MOND_DB_PROJECT CXX)

if(SERVERDB_BUILD)
    message("BUILD SERVER")
    add_subdirectory(ServerDB)
endif()

if(CLIENTDB_BUILD)
    message("BUILD CLIENT")
    add_subdirectory(ClientDB)
endif()