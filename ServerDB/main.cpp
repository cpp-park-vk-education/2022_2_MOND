// Copyright 2022 MOND

#include "Initializer.h"

int main() {
    Initializer dataBase(2);
    dataBase.startDB();

    std::cout << std::thread::hardware_concurrency() << std::endl;

    dataBase.handleCommands();
    dataBase.stopDB();
    return 0;
}
