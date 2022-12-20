// Copyright 2022 MOND

//#include <gtest/gtest.h>

#include "IActionManager.h"
#include "ActionManager.h"


void test_reading(int argc, char** argv){
    for (int i = 0; i < argc; ++i) {
        std::cout << argv[i] << std::endl;
    }

    std::string key;
    std::string value;
    for (int i = 0; i < 10; ++i) {
        key.push_back(static_cast<char>(i));
    }
    for (int i = 0; i < 5000; ++i) {
        value.push_back(static_cast<char>(i));
    }
    std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
    std::cout << "Doing some work\n";


    IActionManager* manager = new ActionManager(argv[1], static_cast<uint16_t>(std::stoi(argv[2])));
    auto ret = manager->CreateTable(argv[3]);

    manager->SelectTable(argv[3]);
    manager->Insert(key, value);

    for (int i = 0; i < 5000; ++i) {
        auto result = manager->Get(key);
//        std::cout << result.size() << std::endl;
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

    std::string key;
    std::string value;
    for (int i = 0; i < 10; ++i) {
        key.push_back(static_cast<char>(i));
    }
    for (int i = 0; i < 5000; ++i) {
        value.push_back(static_cast<char>(i));
    }
    std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
    std::cout << "Doing some work\n";


    IActionManager* manager = new ActionManager(argv[1], static_cast<uint16_t>(std::stoi(argv[2])));
    auto ret = manager->CreateTable(argv[3]);

    manager->SelectTable(argv[3]);
    manager->Insert(key, value);

    for (int i = 0; i < 5000; ++i) {
        key.push_back(static_cast<char>(i));
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
