// Copyright 2022 MOND

//#include <gtest/gtest.h>

#include "IActionManager.h"
#include "ActionManager.h"



int main(int argc, char** argv) {
    std::cout << argc;

    for (int i = 0; i < argc; ++i) {
        std::cout << argv[i] << std::endl;
    }

    std::vector<uint8_t> key;
    std::vector<uint8_t> value;
    for (int i = 0; i < 10; ++i) {
        key.push_back(static_cast<unsigned char>(i));
    }

    for (int i = 0; i < 10000; ++i) {
        value.push_back(static_cast<unsigned char>(i));
    }

    std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
    std::cout << "Doing some work\n";


    IActionManager* manager = new ActionManager(argv[1], static_cast<uint16_t>(std::stoi(argv[2])));
    auto ret = manager->CreateTable(argv[3]);
    std::cout << ret << std::endl;

    manager->SelectTable(argv[3]);

    manager->Insert(key, value);

    for (int i = 0; i < 10000; ++i) {
        auto result = manager->Get(key);
    }

    std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();

    std::chrono::duration<unsigned long long, std::milli> int_ms =
            std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << int_ms.count() << std::endl;

    delete manager;
    return 0;
}
