// Copyright 2022 MOND

//#include <gtest/gtest.h>

#include "IActionManager.h"
#include "ActionManager.h"



int main(int argc, char** argv) {
    std::cout << argc;

    for (int i = 0; i < argc; ++i) {
        std::cout << argv[i] << std::endl;
    }



    IActionManager* manager = new ActionManager(argv[1], static_cast<uint16_t>(std::stoi(argv[2])));
    auto ret = manager->CreateTable(argv[3]);
    std::cout << ret << std::endl;

    std::vector<uint8_t> key;
    std::vector<uint8_t> value;

    for (int i = 0; i < 10; ++i) {
        key.push_back(static_cast<unsigned char>(i));
    }

    for (int i = 0; i < 255; ++i) {
        value.push_back(static_cast<unsigned char>(i));
    }

    manager->Insert(key, value);
    auto result = manager->Get(key);

    for (int i = 0; i < result.size(); ++i) {
        std::cout << result[i];
    }

    delete manager;

    return 0;
}
