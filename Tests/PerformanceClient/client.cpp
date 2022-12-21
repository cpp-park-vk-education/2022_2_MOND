// Copyright 2022 MOND

//#include <gtest/gtest.h>

#include "IActionManager.h"
#include "ActionManager.h"


void test_reading(int argc, char** argv, int V, int N){
    for (int i = 0; i < argc; ++i) {
        std::cout << argv[i] << std::endl;
    }

    std::string key;
    std::string value;
    for (int i = 0; i < 10; ++i) {
        key.push_back(static_cast<char>(i));
    }
    for (int i = 0; i < V; ++i) {
        value.push_back(static_cast<char>(i));
    }
    std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
    std::cout << "Doing some work\n";


    IActionManager* manager = new ActionManager(argv[1], static_cast<uint16_t>(std::stoi(argv[2])));
    auto ret = manager->CreateTable(argv[3]);

    manager->SelectTable(argv[3]);
    manager->Insert(key, value);

    for (int i = 0; i < N; ++i) {
        auto result = manager->Get(key);
    }
    std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();
    std::chrono::duration<unsigned long long, std::milli> int_ms =
            std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << int_ms.count() << std::endl;

    delete manager;
}

void test_writing(int argc, char** argv, int V, int N){
    for (int i = 0; i < argc; ++i) {
        std::cout << argv[i] << std::endl;
    }

    std::string key;
    std::string value;
    for (int i = 0; i < 100; ++i) {
        key.push_back(static_cast<char>(i));
    }
    for (int i = 0; i < V; ++i) {
        value.push_back(static_cast<char>(i));
    }
    std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
    std::cout << "Doing some work\n";


    IActionManager* manager = new ActionManager(argv[1], static_cast<uint16_t>(std::stoi(argv[2])));
    auto ret = manager->CreateTable(argv[3]);

    manager->SelectTable(argv[3]);
    manager->Insert(key, value);

    for (int i = 0; i < N; ++i) {
        key[i % 100] += static_cast<char>(i+i);
        auto result = manager->Insert(key, value);
    }
    std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();
    std::chrono::duration<unsigned long long, std::milli> int_ms =
            std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << int_ms.count() << std::endl;

    delete manager;
}


int main(int argc, char** argv) {

    int V = std::stoi(argv[5]);
    int N = std::stoi(argv[6]);

    if (std::string(argv[4]) == "reading")
        test_reading(argc, argv, V, N);
    else
        test_writing(argc, argv, V, N);

    return 0;
}
