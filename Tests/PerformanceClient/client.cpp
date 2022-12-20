// Copyright 2022 MOND

//#include <gtest/gtest.h>

#include "IActionManager.h"
#include "ActionManager.h"


void test_reading(int argc, char** argv){
    for (int i = 0; i < argc; ++i) {
        std::cout << argv[i] << std::endl;
    }

    std::vector<uint8_t> key;
    std::vector<uint8_t> value;
    for (int i = 0; i < 10; ++i) {
        key.push_back(static_cast<unsigned char>(i));
    }
    for (int i = 0; i < 50000000; ++i) {
        value.push_back(static_cast<unsigned char>(i));
    }
    std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
    std::cout << "Doing some work\n";


    IActionManager* manager = new ActionManager(argv[1], static_cast<uint16_t>(std::stoi(argv[2])));
    auto ret = manager->CreateTable(argv[3]);

    manager->SelectTable(argv[3]);
    manager->Insert(key, value);

    for (int i = 0; i < 500; ++i) {
        auto result = manager->Get(key);
    }
    std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();
    std::chrono::duration<unsigned long long, std::milli> int_ms =
            std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << int_ms.count() << std::endl;

    delete manager;
}

void test_writing(int argc, char** argv){
    for (int i = 0; i < argc; ++i) {
        std::cout << argv[i] << std::endl;
    }

    std::vector<uint8_t> key;
    std::vector<uint8_t> value;
    for (int i = 0; i < 10; ++i) {
        key.push_back(static_cast<unsigned char>(i));
    }
    for (int i = 0; i < 50000000; ++i) {
        value.push_back(static_cast<unsigned char>(i));
    }
    std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
    std::cout << "Doing some work\n";


    IActionManager* manager = new ActionManager(argv[1], static_cast<uint16_t>(std::stoi(argv[2])));
    auto ret = manager->CreateTable(argv[3]);

    manager->SelectTable(argv[3]);
    manager->Insert(key, value);

    for (int i = 0; i < 500; ++i) {
        key[1] += i;
        auto result = manager->Insert(key, value);
    }
    std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();
    std::chrono::duration<unsigned long long, std::milli> int_ms =
            std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << int_ms.count() << std::endl;

    delete manager;
}


int main(int argc, char** argv) {

    if (std::string(argv[4]) == "reading")
        test_reading(argc, argv);
    else
        test_writing(argc, argv);

    return 0;
}
