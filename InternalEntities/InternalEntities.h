// Copyright 2022 mora

#ifndef MOND_DB_INTERNALENTITIES_H
#define MOND_DB_INTERNALENTITIES_H

#include <iostream>

enum class requestType{
    INSERT = 0,
    REMOVE,
    FIND,
    CLEAR,
    GET_SIZE,
    GET,
    UPDATE,
    CREATE_TABLE = 100,
    DELETE_TABLE,
    GET_TABLE,
    GET_NUM_TABLES,
    SHOW_TABLES
};

enum class Status {
    NOTHING = 0,
    READY,
    WORKING,
    OK,
    FAILURE
};

struct Request{
    requestType type;
    Status status;
    size_t key_len;
    size_t value_len;
    uint8_t *key;
    uint8_t *value;
    std::string table_name;
};

#endif //MOND_DB_INTERNALENTITIES_H